package org.lineageos.dt2w.sm6375;

import android.app.Service;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.database.ContentObserver;
import android.net.Uri;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.SystemProperties;
import android.os.UserHandle;
import android.provider.Settings.Secure;

public class DT2WServiceSM6375 extends Service {
    private static final String TAG = "DT2WServiceSM6375";
    private Context mContext;

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startid) {
        mContext = this;
        Handler mHandler = new Handler(Looper.getMainLooper());
        CustomSettingsObserver mCustomSettingsObserver = new CustomSettingsObserver(mHandler);
        mCustomSettingsObserver.observe();
        mCustomSettingsObserver.update();
        return START_STICKY;
    }

    private class CustomSettingsObserver extends ContentObserver {
        CustomSettingsObserver(Handler handler) {
            super(handler);
        }

        void observe() {
            ContentResolver resolver = mContext.getContentResolver();
            resolver.registerContentObserver(Secure.getUriFor(Secure.DOUBLE_TAP_TO_WAKE),
                    false, this, UserHandle.USER_CURRENT);
        }

        void update() {
            ContentResolver resolver = mContext.getContentResolver();
            int dt2wValue = Secure.getInt(resolver, Secure.DOUBLE_TAP_TO_WAKE, 0) ? 1 : 0;
            SystemProperties.set("persist.sys.sm6375.dt2w", dt2wValue);
        }

        @Override
        public void onChange(boolean selfChange, Uri uri) {
            if (uri.equals(Secure.getUriFor(Secure.DOUBLE_TAP_TO_WAKE))) {
                update();
            }
        }
    }
}
