package org.chromium.chrome.browser.firstrun;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import org.chromium.base.Log;
import org.chromium.chrome.R;
import android.support.v4.view.ViewPager;

/**
 * Created by elvis on 25.11.16.
 */
public class IntroFragment extends FirstRunPage {

    private ViewPager viewPager;
    private LinearLayout indicator;

    private Button launchBrowser;
    private Button nextButton;
    private Button skipButton;

    private IntroPagerAdapter adapter;
    private ImageView[] indicatorPages ;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fre_intro, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        indicator = (LinearLayout) view.findViewById(R.id.viewpager_indicator);

        indicatorPages = new ImageView[3];
        indicatorPages[0] = (ImageView) view.findViewById(R.id.page1);
        indicatorPages[1] = (ImageView) view.findViewById(R.id.page2);
        indicatorPages[2] = (ImageView) view.findViewById(R.id.page3);


        viewPager = (ViewPager) view.findViewById(R.id.viewpager);
        adapter = new IntroPagerAdapter(getActivity());
        viewPager.setAdapter(adapter);
        viewPager.setOffscreenPageLimit(3);
        viewPager.addOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
            @Override
            public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {
                adapter.updateView(position, positionOffset);
            }

            @Override
            public void onPageSelected(int position) {
                super.onPageSelected(position);
                for(int i = 0; i < indicatorPages.length; i++) {
                    indicatorPages[i].setImageResource(i == position ? R.drawable.point_black :  0);
                }

                nextButton.setVisibility(position == 2 ? View.GONE : View.VISIBLE);
                skipButton.setVisibility(position == 2 ? View.GONE : View.VISIBLE);
                launchBrowser.setVisibility(position == 2 ? View.VISIBLE : View.GONE);
            }
        });

        skipButton = (Button) view.findViewById(R.id.skip_button);
        skipButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                advanceToNextPage();
            }
        });


        nextButton = (Button) view.findViewById(R.id.next_button);
        nextButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                viewPager.setCurrentItem(viewPager.getCurrentItem() + 1, true);
            }
        });

        launchBrowser = (Button) view.findViewById(R.id.launch_browser);
        launchBrowser.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                advanceToNextPage();
            }
        });
        launchBrowser.setVisibility(View.GONE);
    }
}
