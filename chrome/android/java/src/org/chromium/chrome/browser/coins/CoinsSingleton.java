package org.chromium.chrome.browser.coins;

import android.content.Context;
import android.content.SharedPreferences;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.TimeUnit;

/**
 * Created by elvis on 28.11.16.
 */
public class CoinsSingleton {
    public static final String COIN_COUNT = "coin_count";
    public static final String LAST_TIME_INC = "last_time_inc";
    private static final String ONE_SURF_REWARD = "one_surf_reward";
    private static CoinsSingleton instance = new CoinsSingleton();

    public static CoinsSingleton getInstance() {
        return instance;
    }
    private float value = 0;
    private CoinType currentType = CoinType.MASS_COIN;
    private List<ChangeListener> changeListeners = new ArrayList<ChangeListener>();

    private Map<CoinType, Float> quotations = new HashMap<CoinType, Float>();
    private float oneSurfValue = 0.01f;

    private SharedPreferences sharedPreferences;
    private long lastTimeInc = 0;
    public void init(Context context) {
        sharedPreferences = context.getSharedPreferences("coins", Context.MODE_PRIVATE);
        value = sharedPreferences.getFloat(COIN_COUNT, 0);
        oneSurfValue = sharedPreferences.getFloat(ONE_SURF_REWARD, 0.01f);
    }

    public void setQuotation(CoinType coinType, float value) {
        quotations.put(coinType, value);
    }

    public CoinsSingleton() {
        quotations.put(CoinType.MASS_COIN, 1f);
        quotations.put(CoinType.BIT_COIN, 0f);
        quotations.put(CoinType.DOLLAR, 0f);
    }

    public void setCurrentType(CoinType currentType) {
        if(this.currentType != currentType) {
            this.currentType = currentType;
            fireTypeChanged(currentType);
        }
    }

    public SharedPreferences getSharedPreferences() {
        return sharedPreferences;
    }

    public void setValue(CoinType type, float value) {
        setValue(quotations.get(type) != 0 ?  value / quotations.get(type) : 0);
    }

    public void setOneSurfValue(float oneSurfValue) {
        this.oneSurfValue = oneSurfValue;
        if(sharedPreferences != null) {
            sharedPreferences.edit().putFloat(ONE_SURF_REWARD, oneSurfValue).apply();
        }
    }

//    private SecretKeySpec secretKey() {
//        SecretKeySpec sks = null;
//        try {
//            SecureRandom sr = SecureRandom.getInstance("SHA1PRNG");
//            sr.setSeed("any data used as random seed".getBytes());
//            KeyGenerator kg = KeyGenerator.getInstance("AES");
//            kg.init(128, sr);
//            sks = new SecretKeySpec((kg.generateKey()).getEncoded(), "AES");
//        } catch (Exception e) {
//            Log.e("crypt", "secret key spec error");
//        }
//        byte[] encodedBytes = null;
//        try {
//            Cipher c = Cipher.getInstance("AES");
//            c.init(Cipher.ENCRYPT_MODE, secretKey());
//            encodedBytes = c.doFinal(String.valueOf(value).getBytes());
//        } catch (Exception e) {
//            Log.e("crypt", "AES encryption error");
//        }
//        return sks;
//    }

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
            setValue(CoinType.MASS_COIN, getValue(CoinType.MASS_COIN) + oneSurfValue);
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
        return value * quotations.get(type);
    }

    public interface ChangeListener {
        void onTypeChanged(CoinType newType);

        void onValueChanged(float oldValue, float newValue);
    }
}
