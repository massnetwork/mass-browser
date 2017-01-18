package org.chromium.chrome.browser.init.tasks;

import android.os.AsyncTask;
import android.util.JsonReader;
import org.chromium.base.Log;
import org.chromium.chrome.browser.coins.CoinType;
import org.chromium.chrome.browser.coins.CoinsSingleton;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by elvis on 06.01.17.
 */
public class GetCurrencyTask extends AsyncTask<Void, Void, Void> {
    @Override
    protected Void doInBackground(Void... voids) {

        try {

            URL url = new URL("http://adverttool.ru/currency");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            InputStream stream = connection.getInputStream();
            BufferedReader streamReader = new BufferedReader(new InputStreamReader(stream, "UTF-8"));
            StringBuilder responseStrBuilder = new StringBuilder();
            String inputStr;
            while ((inputStr = streamReader.readLine()) != null) {
                responseStrBuilder.append(inputStr);
            }
            JSONObject jsonObject = new JSONObject(responseStrBuilder.toString());
            CoinsSingleton.getInstance().setQuotation(CoinType.BIT_COIN, (float) jsonObject.getDouble("btc"));
            CoinsSingleton.getInstance().setQuotation(CoinType.DOLLAR, (float) jsonObject.getDouble("dollar"));
            stream.close();
            connection.disconnect();
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return null;
    }
}
