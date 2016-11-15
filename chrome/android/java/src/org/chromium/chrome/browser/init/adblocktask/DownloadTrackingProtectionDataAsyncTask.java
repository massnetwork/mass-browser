package org.chromium.chrome.browser.init.adblocktask;

import android.os.AsyncTask;
import org.chromium.chrome.browser.init.ADBlockUtils;
import android.content.Context;

public class DownloadTrackingProtectionDataAsyncTask extends AsyncTask<Void,Void,Long> {

    private Context mContext;

    public DownloadTrackingProtectionDataAsyncTask(Context mContext) {
        this.mContext = mContext;
    }

    protected Long doInBackground(Void... params) {
        String verNumber = ADBlockUtils.getDataVerNumber(
            ADBlockUtils.TRACKING_PROTECTION_URL);
        ADBlockUtils.readData(mContext,
            ADBlockUtils.TRACKING_PROTECTION_LOCALFILENAME,
            ADBlockUtils.TRACKING_PROTECTION_URL,
            ADBlockUtils.ETAG_PREPEND_TP, verNumber,
            ADBlockUtils.TRACKING_PROTECTION_LOCALFILENAME_DOWNLOADED, true);

        ADBlockUtils.CreateDownloadedFile(mContext, ADBlockUtils.TRACKING_PROTECTION_LOCALFILENAME,
            verNumber, ADBlockUtils.TRACKING_PROTECTION_LOCALFILENAME_DOWNLOADED);

        return null;
    }
}