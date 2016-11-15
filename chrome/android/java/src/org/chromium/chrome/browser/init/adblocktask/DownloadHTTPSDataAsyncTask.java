package org.chromium.chrome.browser.init.adblocktask;

import android.os.AsyncTask;
import org.chromium.chrome.browser.init.ADBlockUtils;
import android.content.Context;

public class DownloadHTTPSDataAsyncTask extends AsyncTask<Void, Void, Long> {

    private Context mContext;

    public DownloadHTTPSDataAsyncTask(Context mContext) {
        this.mContext = mContext;
    }

    protected Long doInBackground(Void... params) {
        String verNumber = ADBlockUtils.getDataVerNumber(
                ADBlockUtils.HTTPS_URL);
        ADBlockUtils.readData(mContext,
                ADBlockUtils.HTTPS_LOCALFILENAME,
                ADBlockUtils.HTTPS_URL,
                ADBlockUtils.ETAG_PREPEND_HTTPS, verNumber,
                ADBlockUtils.HTTPS_LOCALFILENAME_DOWNLOADED, true);

        ADBlockUtils.CreateDownloadedFile(mContext, ADBlockUtils.HTTPS_LOCALFILENAME,
                verNumber, ADBlockUtils.HTTPS_LOCALFILENAME_DOWNLOADED);

        return null;
    }
}