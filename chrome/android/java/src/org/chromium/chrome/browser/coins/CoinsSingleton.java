package org.chromium.chrome.browser.coins;

/**
 * Created by elvis on 28.11.16.
 */
public class CoinsSingleton {
    private static CoinsSingleton instance = new CoinsSingleton();

    public static CoinsSingleton getInstance() {
        return instance;
    }
    private float value = 0.0736f;
    private CoinType currentType = CoinType.MASS_COIN;
    private ChangeListener changeListener;

    public void setCurrentType(CoinType currentType) {
        this.currentType = currentType;
        if(changeListener != null) {
            changeListener.onTypeChanged(currentType);
        }
    }

    public void setChangeListener(ChangeListener changeListener) {
        this.changeListener = changeListener;
    }

    public CoinType getCurrentType() {
        return currentType;
    }

    public float getValue() {
        return getValue(currentType);
    }
    public float getValue(CoinType type) {
        return value * type.getRatio();
    }

    public interface ChangeListener {
        void onTypeChanged(CoinType newType);

        void onValueChanged(float newBaseValue, float newTypeValue);
    }
}
