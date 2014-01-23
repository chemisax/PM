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
        ofSetColor(255,255,255);
        ofRect(20,20,600,20);
        ofSetColor(0,0,0);
        ofDrawBitmapString("A"+ofToString(alert_id) + ": "+msg, 25, 35);
        counter ++;
    } else if (counter == life) {
        live = false;
    }
}