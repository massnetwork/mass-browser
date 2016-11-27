package org.chromium.chrome.browser.firstrun;

import android.content.Context;
import android.support.v4.view.PagerAdapter;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import org.chromium.chrome.R;

/**
 * Created by elvis on 25.11.16.
 */
public class IntroPagerAdapter extends PagerAdapter {

    private int[] layouts = new int[] {R.layout.fre_no_unwanted_ads, R.layout.fre_no_data_harvesting, R.layout.fre_final_make_money};
    private Context mContext;

    public IntroPagerAdapter(Context context) {
        mContext = context;
    }

    @Override
    public Object instantiateItem(ViewGroup collection, int position) {
        LayoutInflater inflater = LayoutInflater.from(mContext);
        ViewGroup layout = (ViewGroup) inflater.inflate(layouts[position], collection, false);
        collection.addView(layout);
        return layout;
    }

    @Override
    public void destroyItem(ViewGroup container, int position, Object object) {
        container.removeView((View) object);
    }

    @Override
    public int getCount() {
        return layouts.length;
    }

    @Override
    public boolean isViewFromObject(View view, Object object) {
        return view == object;
    }
}
