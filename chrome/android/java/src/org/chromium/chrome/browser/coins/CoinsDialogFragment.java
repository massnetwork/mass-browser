package org.chromium.chrome.browser.coins;

import android.app.DialogFragment;
import android.app.Fragment;
import android.os.Bundle;
import android.support.annotation.IdRes;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import org.chromium.chrome.R;

/**
 * Created by elvis on 27.11.16.
 */
public class CoinsDialogFragment extends DialogFragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.coins_dialog, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        RadioGroup radioGroup = (RadioGroup)view.findViewById(R.id.coin_group);

        RadioButton masscoin = (RadioButton) view.findViewById(R.id.masscoin);
        masscoin.setText(String.valueOf(CoinsSingleton.getInstance().getValue(CoinType.MASS_COIN)));
        masscoin.setTag(CoinType.MASS_COIN);
        masscoin.setChecked(CoinsSingleton.getInstance().getCurrentType() == CoinType.MASS_COIN);

        RadioButton bitcoin = (RadioButton) view.findViewById(R.id.bitcoin);
        bitcoin.setText(String.valueOf(CoinsSingleton.getInstance().getValue(CoinType.BIT_COIN)));
        bitcoin.setTag(CoinType.BIT_COIN);
        bitcoin.setChecked(CoinsSingleton.getInstance().getCurrentType() == CoinType.BIT_COIN);

        RadioButton dollar = (RadioButton) view.findViewById(R.id.dollar);
        dollar.setText(String.valueOf(CoinsSingleton.getInstance().getValue(CoinType.DOLLAR)));
        dollar.setTag(CoinType.DOLLAR);
        dollar.setChecked(CoinsSingleton.getInstance().getCurrentType() == CoinType.DOLLAR);

        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, @IdRes int viewId) {
                CoinType type = (CoinType) radioGroup.findViewById(viewId).getTag();
                CoinsSingleton.getInstance().setCurrentType(type);
            }
        });
    }
}
