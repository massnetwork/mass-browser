// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.webapps;

import android.graphics.Bitmap;
import android.text.TextUtils;

import org.chromium.base.annotations.CalledByNative;
import org.chromium.chrome.browser.tab.EmptyTabObserver;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.content_public.browser.WebContents;

import java.util.HashMap;

/**
 * Downloads the Web Manifest if the web site still uses the {@link manifestUrl} passed to the
 * constructor.
 */
public class ManifestUpgradeDetectorFetcher extends EmptyTabObserver {

    /**
     * Called once the Web Manifest has been downloaded.
     */
    public interface Callback {
        /**
         * @param fetchedInfo The fetched Web Manifest data.
         * @param bestIconUrl Icon URL in {@link data} which is best suited for use as the launcher
         *                    icon on this device.
         */
        void onGotManifestData(WebApkInfo fetchedInfo, String bestIconUrl);
    }

    /**
     * Pointer to the native side ManifestUpgradeDetectorFetcher. The Java side owns the native side
     * ManifestUpgradeDetectorFetcher.
     */
    private long mNativePointer;

    /** The tab that is being observed. */
    private Tab mTab;

    /**
     * Web Manifest data at time that the WebAPK was generated.
     */
    private WebApkInfo mOldInfo;

    private Callback mCallback;

    /**
     * Starts fetching the web manifest resources.
     * @param callback Called once the Web Manifest has been downloaded.
     */
    public boolean start(Tab tab, WebApkInfo oldInfo, Callback callback) {
        if (tab.getWebContents() == null || TextUtils.isEmpty(oldInfo.manifestUrl())) {
            return false;
        }

        mTab = tab;
        mOldInfo = oldInfo;
        mNativePointer = nativeInitialize(mOldInfo.scopeUri().toString(), mOldInfo.manifestUrl());
        mCallback = callback;
        mTab.addObserver(this);
        nativeStart(mNativePointer, mTab.getWebContents());
        return true;
    }

    /**
     * Puts the object in a state where it is safe to be destroyed.
     */
    public void destroy() {
        mTab.removeObserver(this);
        nativeDestroy(mNativePointer);
        mNativePointer = 0;
    }

    @Override
    public void onWebContentsSwapped(Tab tab, boolean didStartLoad,
            boolean didFinishLoad) {
        updatePointers();
    }

    @Override
    public void onContentChanged(Tab tab) {
        updatePointers();
    }

    /**
     * Updates which WebContents the native ManifestUpgradeDetectorFetcher is monitoring.
     */
    private void updatePointers() {
        nativeReplaceWebContents(mNativePointer, mTab.getWebContents());
    }

    /**
     * Called when the updated Web Manifest has been fetched.
     */
    @CalledByNative
    protected void onDataAvailable(String startUrl, String scopeUrl, String name, String shortName,
            String bestIconUrl, String bestIconMurmur2Hash, Bitmap bestIconBitmap,
            String[] iconUrls, int displayMode, int orientation, long themeColor,
            long backgroundColor) {
        HashMap<String, String> iconUrlToMurmur2HashMap = new HashMap<String, String>();
        for (String iconUrl : iconUrls) {
            String murmur2Hash = (iconUrl.equals(bestIconUrl)) ? bestIconMurmur2Hash : null;
            iconUrlToMurmur2HashMap.put(iconUrl, murmur2Hash);
        }

        WebApkInfo info = WebApkInfo.create(mOldInfo.id(), startUrl, scopeUrl,
                new WebApkInfo.Icon(bestIconBitmap), name, shortName, displayMode, orientation,
                mOldInfo.source(), themeColor, backgroundColor, mOldInfo.webApkPackageName(),
                mOldInfo.shellApkVersion(), mOldInfo.manifestUrl(), startUrl,
                iconUrlToMurmur2HashMap);
        mCallback.onGotManifestData(info, bestIconUrl);
    }

    private native long nativeInitialize(String scope, String webManifestUrl);
    private native void nativeReplaceWebContents(
            long nativeManifestUpgradeDetectorFetcher, WebContents webContents);
    private native void nativeDestroy(long nativeManifestUpgradeDetectorFetcher);
    private native void nativeStart(
            long nativeManifestUpgradeDetectorFetcher, WebContents webContents);
}
