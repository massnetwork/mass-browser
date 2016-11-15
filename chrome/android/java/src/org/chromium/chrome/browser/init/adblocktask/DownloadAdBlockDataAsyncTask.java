package org.chromium.chrome.browser.init.adblocktask;

import android.os.AsyncTask;
import org.chromium.chrome.browser.init.ADBlockUtils;
import android.content.Context;

public class DownloadAdBlockDataAsyncTask extends AsyncTask<Void, Void, Long> {

    private Context mContext;

    public DownloadAdBlockDataAsyncTask(Context mContext) {
        this.mContext = mContext;
    }

    protected Long doInBackground(Void... params) {
        String verNumber = ADBlockUtils.getDataVerNumber(
                ADBlockUtils.ADBLOCK_URL);
        ADBlockUtils.readData(mContext,
                ADBlockUtils.ADBLOCK_LOCALFILENAME,
                ADBlockUtils.ADBLOCK_URL,
                ADBlockUtils.ETAG_PREPEND_ADBLOCK, verNumber,
                ADBlockUtils.ADBLOCK_LOCALFILENAME_DOWNLOADED, true);

        ADBlockUtils.CreateDownloadedFile(mContext, ADBlockUtils.ADBLOCK_LOCALFILENAME,
                verNumber, ADBlockUtils.ADBLOCK_LOCALFILENAME_DOWNLOADED);

        return null;
    }
}