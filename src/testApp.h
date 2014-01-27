#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "alertSystem.h"
#include "messenger.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"

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
    
        void exit();
    
        int backgroundColor[3] = {0,0,0};
        int spectrumColor[3] = {120,15,255};
    
        ofxKinect kinect;
        alertSystem *Alert;
        messenger *Messenger;
        ofSoundPlayer soundPlayer;
        ofxOscMessage msgOut;
        ofxCvColorImage colorImg;
    
        void drawCalibrationLines();
        void updateMessenger();
        bool calibrating;
    
};