package org.chromium.chrome.browser.coins;

import org.chromium.chrome.R;

/**
 * Created by elvis on 28.11.16.
 */
public enum CoinType {
    MASS_COIN(R.drawable.masscoin_selector),
    BIT_COIN(R.drawable.bitcoin_selector),
    DOLLAR(R.drawable.dollar_selector);


    private int iconRes;
    CoinType(int res) {
        iconRes = res;
    }

    public int getIconRes() {
        return iconRes;
    }

}
