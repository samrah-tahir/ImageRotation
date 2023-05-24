package com.example.myapplication;

import org.qtproject.qt.android.bindings.QtActivity;
import android.Manifest;
import android.os.Bundle;
import android.content.*;
import android.view.OrientationEventListener;

public class MainActivity extends QtActivity {


    public native void setNativeRotation(int rotation, long pointer);

    public long pointer;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Orientation mOrientation = new Orientation(this);
        mOrientation.enable();
    }


    public void setPointer(long ptr){
        pointer = ptr;
    }

    //orietation change
    public class Orientation extends OrientationEventListener {
        public Orientation(Context context){
            super(context);
        }

        @Override
        public void onOrientationChanged(int orientation){
//            if(orientation >= 90 || orientation >= 0 || orientation <= 270)
                setNativeRotation(orientation, pointer);
        }
    }
}
