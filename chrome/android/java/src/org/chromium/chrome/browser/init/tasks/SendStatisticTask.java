package org.chromium.chrome.browser.init.tasks;

import android.content.Context;
import android.os.AsyncTask;
import android.provider.Settings;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by elvis on 18.01.17.
 */
public class SendStatisticTask extends AsyncTask<Void, Void, Void> {
    public static final String URL_ADD_STAT = "http://adverttool.ru/api/v1/statistic/add.php?id=_ID_";

    private Context context;
    private String data;

    public SendStatisticTask(Context context, String data) {
        this.context = context;
        this.data = data;
    }

    @Override
    protected Void doInBackground(Void... voids) {
        try {
            URL url = new URL(URL_ADD_STAT.replace("_ID_", Settings.Secure.getString(context.getContentResolver(), Settings.Secure.ANDROID_ID)));

            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setDoOutput(true);
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type", "plain/text");
            connection.setRequestProperty("charset", "utf-8");
            connection.setRequestProperty("Content-Length", Integer.toString(data.length()));
            connection.setUseCaches(false);

            OutputStream outputStream = connection.getOutputStream();
            DataOutputStream wr = new DataOutputStream(outputStream);
            wr.write(data.getBytes());
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
}
