package org.chromium.chrome.browser.coins;

import android.app.DialogFragment;
import android.app.Fragment;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.support.annotation.IdRes;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import org.chromium.chrome.R;

import java.text.DecimalFormat;

/**
 * Created by elvis on 27.11.16.
 */
public class CoinsDialogFragment extends DialogFragment {
    private RadioButton masscoin;
    private RadioButton bitcoin;
    private RadioButton dollar;

    private CoinsSingleton.ChangeListener changeListener;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.coins_dialog, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        RadioGroup radioGroup = (RadioGroup)view.findViewById(R.id.coin_group);

        masscoin = (RadioButton) view.findViewById(R.id.masscoin);
        masscoin.setTag(CoinType.MASS_COIN);


        bitcoin = (RadioButton) view.findViewById(R.id.bitcoin);
        bitcoin.setTag(CoinType.BIT_COIN);


        dollar = (RadioButton) view.findViewById(R.id.dollar);
        dollar.setTag(CoinType.DOLLAR);


        updateCoins();

        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, @IdRes int viewId) {
                CoinType type = (CoinType) radioGroup.findViewById(viewId).getTag();
                CoinsSingleton.getInstance().setCurrentType(type);
            }
        });


        CoinsSingleton.getInstance().addChangeListener(changeListener = new CoinsSingleton.ChangeListener() {
            @Override
            public void onTypeChanged(CoinType newType) {
            }

            @Override
            public void onValueChanged(float oldValue, float newValue) {
                new Handler(Looper.getMainLooper()).post(new Runnable() {
                    @Override
                    public void run() {
                        updateCoins();
                    }
                });
            }
        });
    }

    private void updateCoins() {
        DecimalFormat decimalFormat = new DecimalFormat("#.####");
        masscoin.setText(decimalFormat.format(CoinsSingleton.getInstance().getValue(CoinType.MASS_COIN)));
        masscoin.setChecked(CoinsSingleton.getInstance().getCurrentType() == CoinType.MASS_COIN);

        bitcoin.setText(decimalFormat.format(CoinsSingleton.getInstance().getValue(CoinType.BIT_COIN)));
        bitcoin.setChecked(CoinsSingleton.getInstance().getCurrentType() == CoinType.BIT_COIN);

        dollar.setText(decimalFormat.format(CoinsSingleton.getInstance().getValue(CoinType.DOLLAR)));
        dollar.setChecked(CoinsSingleton.getInstance().getCurrentType() == CoinType.DOLLAR);
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        CoinsSingleton.getInstance().removeChangeListener(changeListener);
    }
}
