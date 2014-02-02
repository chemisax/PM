#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "alertSystem.h"
#include "messenger.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"
#include "screenAnimation.h"
#include <list>
#include "surface.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        alertSystem *Alert;
        messenger *Messenger;
        ofSoundPlayer soundPlayer;
        ofxOscMessage msgOut,waveMsg;
        list<screenAnimation *> lines;
        list<screenAnimation *> :: iterator itr;
        ofImage calibration;
    
        int backgroundColor[3] = {0,0,0},
            longestDistance,
            soundDuration,
            defaultRate,
            rateCounter,
            heikin_update_rate,
            heikin_counter,
            heikin_update_current,
            oscduration,
            kinect_last_update,
            kinect_tolerance,
            heikin[3],
            line_counter,
            frameCounter,
            ami_alpha,
            frame_counter_ami;
        float rate,
            beat_rate;
        bool calibrating,ami_yonda;
        surface *amiSurface;
    
    
        void exit();
        void drawCalibrationLines();
        void updateMessenger();
        void update_bpm();
        void heartBeat ();
        void Lines();
        void ami_draw();
};
