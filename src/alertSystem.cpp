//
//  alert.cpp
//  AMI
//
//  Created by José María Campaña Rojas on 23/01/14.
//
//

#include "alertSystem.h"
#include "ofMain.h"

alertSystem::alertSystem(int live_time) {
    life = live_time;
    live = false;
    counter = 0;
    alert_id = 0;
    msg = "";
}

void alertSystem::show(string s_msg) {
    msg = s_msg;
    counter = 0;
    alert_id++;
    live = true;
    ofLog(OF_LOG_NOTICE, msg);
}

void alertSystem::draw() {
    if (live && counter <= life) {
        ofSetColor(255,255,255,fadeGetAlpha(0.8));
        ofRect(20,20,ofGetWidth()-40,20);
        ofSetColor(0,0,0,fadeGetAlpha(0.8));
        ofDrawBitmapString("A"+ofToString(alert_id) + ": "+msg, 25, 35);
        counter ++;
    } else if (counter == life) {
        live = false;
    }
}

int alertSystem::fadeGetAlpha (float startFrom) {
    if (counter > (life*startFrom)) {
        int total = (int)(life*0.3);
        int currentFrame = total+(counter-life);
        int percent = 100-(currentFrame*100/total);
        int pValue = (int)(255*(float)percent/100);
        return pValue;
    } else {
        return 255;
    }
}