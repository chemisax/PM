#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "alertSystem.h"
#include "messenger.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"

#include <list>

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
        ofxOscMessage msgOut;
        list<alertSystem *> lines;
        list<alertSystem *> :: iterator itr;
    
        int spectrumColor[3] = {120,15,255},
            backgroundColor[3] = {0,0,0},
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
            heikin[3];
        float rate,
            beat_rate;
        bool calibrating;
        
        void exit();
        void drawCalibrationLines();
        void updateMessenger();
        void spectrum();
        void update_bpm();
        void heartBeat ();
    
};
