package org.chromium.chrome.browser.coins;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Handler;
import android.os.Looper;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

/**
 * Created by elvis on 28.11.16.
 */
public class CoinsSingleton {
    public static final String COIN_COUNT = "coin_count";
    public static final String LAST_TIME_INC = "last_time_inc";
    private static CoinsSingleton instance = new CoinsSingleton();

    public static CoinsSingleton getInstance() {
        return instance;
    }
    private float value = 0;
    private CoinType currentType = CoinType.MASS_COIN;
    private List<ChangeListener> changeListeners = new ArrayList<ChangeListener>();

    private SharedPreferences sharedPreferences;
    private long lastTimeInc = 0;
    public void init(Context context) {
        sharedPreferences = context.getSharedPreferences("coins", Context.MODE_PRIVATE);
        value = sharedPreferences.getFloat(COIN_COUNT, 0);
    }

    public CoinsSingleton() {
    }

    public void setCurrentType(CoinType currentType) {
        if(this.currentType != currentType) {
            this.currentType = currentType;
            fireTypeChanged(currentType);
        }
    }

    public void setValue(CoinType type, float value) {
        setValue(value / type.getRatio());
    }

    public void setValue(float value) {
        float old = this.value;
        this.value = value;
        if(sharedPreferences != null) {
            sharedPreferences.edit().putFloat(COIN_COUNT, value).apply();
        }
        fireValueChanged(old, value);
    }

    public void addChangeListener(ChangeListener changeListener) {
        this.changeListeners.add(changeListener);
    }
    public void removeChangeListener(ChangeListener changeListener) {
        this.changeListeners.remove(changeListener);
    }

    private void fireTypeChanged(CoinType currentType) {
        for (ChangeListener changeListener : changeListeners) {
            if(changeListener != null) {
                changeListener.onTypeChanged(currentType);
            }
        }
    }

    private void fireValueChanged(float old,float value) {
        for (ChangeListener changeListener : changeListeners) {
            if(changeListener != null) {
                changeListener.onValueChanged(old, value);
            }
        }
    }

    public void surfing() {
        if(lastTimeInc == 0 && sharedPreferences != null) {
            lastTimeInc = sharedPreferences.getLong(LAST_TIME_INC, 0);
        }
        long newLastTimeInc = System.currentTimeMillis();
        if(newLastTimeInc - TimeUnit.MINUTES.toMillis(1) > lastTimeInc) {
            setValue(CoinType.MASS_COIN, getValue(CoinType.MASS_COIN) + 0.01f);
            lastTimeInc = newLastTimeInc;
            if(sharedPreferences != null) {
                sharedPreferences.edit().putLong(LAST_TIME_INC, lastTimeInc).apply();
            }
        }
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

        void onValueChanged(float oldValue, float newValue);
    }
}
