package org.chromium.chrome.browser.coins;

import org.chromium.chrome.R;

/**
 * Created by elvis on 28.11.16.
 */
public enum CoinType {
    MASS_COIN(1f, R.drawable.masscoin_selector),
    BIT_COIN(1.17f, R.drawable.bitcoin_selector),
    DOLLAR(642f, R.drawable.dollar_selector);


    private float ratio;
    private int iconRes;
    CoinType(float rat, int res) {
        ratio = rat;
        iconRes = res;
    }

    public int getIconRes() {
        return iconRes;
    }

    public float getRatio() {
        return ratio;
    }

}
