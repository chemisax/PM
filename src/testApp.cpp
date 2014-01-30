#include "testApp.h"
#include "ofMain.h"
#include "ofxOsc.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(30);
    
    //initialize variables
    calibrating = true;
    
    //Start the alert system
    Alert = new alertSystem(30*2);
    Alert -> show("Welcome to AMI Master <3");
    
    //Start the messenger system
    Messenger = new messenger();
    
    //Start the sound
    soundPlayer.loadSound("hb.mp3");
    
    //soundEvent
    
    soundDuration = 22; // frames
    defaultRate = 90; //frames
    rateCounter = 0;
    
    beat_rate = defaultRate;
    heikin_update_rate = 10;
    heikin_update_current = 0;
    longestDistance = 450;
    heikin_counter = 0;
    oscduration = 0;
    for (int i=0; i<3; i++) heikin[i] = defaultRate;

    kinect_last_update = 0;
    kinect_tolerance = 30;
}

//--------------------------------------------------------------
void testApp::update(){
    
    //Get new messages and parse them
    updateMessenger();

    //Set background color
    ofBackground(backgroundColor[0], backgroundColor[1], backgroundColor[2]);
    
    //RateCounter
    if ((ofGetFrameNum()-kinect_last_update) <= kinect_tolerance) {
        if (heikin_update_current == heikin_update_rate) {
            heikin_update_current = 0;
            heikin[heikin_counter] = oscduration;
            
            if (heikin_counter == 3) {
                heikin_counter = 0;
                rate = ((float)((heikin[0]+heikin[1]+heikin[2])/3)/longestDistance)*defaultRate;
                beat_rate = ((int)rate > soundDuration) ? rate : soundDuration+1;
                //cout << beat_rate << endl;
            } else {
                heikin_counter++;
            }
            
        } else {
            heikin_update_current++;
        }
    } else {
        beat_rate = defaultRate;
    }
    
}

//--------------------------------------------------------------
void testApp::draw() {


    //Draw the spectrum of the song
    int divs = 50;
    float *spectrum = ofSoundGetSpectrum(divs);
    ofxOscMessage spect;
    spect.setAddress("AMI/master/display1/spectrum");
    
    for (int i=0; i<divs; i++) {
        ofSetColor(spectrumColor[0],spectrumColor[1],spectrumColor[2]);
        spect.addFloatArg(spectrum[i]);
        ofRect((ofGetWidth()/divs)*i, 0, ofGetWidth()/divs, spectrum[i]*ofGetHeight());
    }
    
    
    // Send the spectrum to the other display
    Messenger -> sendOSC(spect, false);
    spect.clear();
    
    //Draw calibration lines
    drawCalibrationLines();
    
    //play heartbeat/call line
    if (rateCounter >= (int) beat_rate) {
        rateCounter = 0;
        soundPlayer.play();
        
        line = new Line();
        line -> play();
        
    } else {
        rateCounter ++;
    }

    //cout << rateCounter << endl;
    
    // Calls for classes that write to the screen
    Alert -> draw();
}

//--------------------------------------------------------------
void testApp::drawCalibrationLines () {
    if (calibrating) {
        ofSetColor(255,255,255);
        ofLine(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2);
        ofLine(ofGetWidth()/2, (ofGetHeight()/2)-20, ofGetWidth()/2, (ofGetHeight()/2)+20);
    }
}

//--------------------------------------------------------------
void testApp::updateMessenger() {
    
    msgOut = Messenger -> update();
    
    if (msgOut.getAddress() != "empty"){
        
        if (msgOut.getAddress() == "/ami/webClient/order") {
            
            //Alert -> show(msgOut.getArgAsString(0));
            
            // Switch for the different orders from Node.js
            if (msgOut.getArgAsString(0) == "play") {
                
                soundPlayer.setPaused(false);
            
            } else if (msgOut.getArgAsString(0) == "stop") {
                
                soundPlayer.setPaused(true);
            
            } else if (msgOut.getArgAsString(0) == "status") {
                
                ofxOscMessage mess;
                mess.setAddress("AMI/master/broadcast/status");
                mess.addStringArg("AMI Master/Server is online");
                Messenger -> sendOSC(mess, true);
            
            } else if (msgOut.getArgAsString(0) == "chbg") {
                
                for (int i=0; i<3; i++) backgroundColor[i] = ofRandom(0,255);
                ofxOscMessage background;
                background.setAddress("AMI/master/display1/background");
                for (int i=0; i<3; i++) background.addIntArg(ofRandom(0,255));
                Messenger -> sendOSC(background, false);
            
            } else if (msgOut.getArgAsString(0) == "chclr") {
                
                for (int i=0; i<3; i++) spectrumColor[i] = ofRandom(0,255);
                ofxOscMessage spect;
                spect.setAddress("AMI/master/display1/spectrumChange");
                for (int i=0; i<3; i++) spect.addIntArg(ofRandom(0,255));
                Messenger -> sendOSC(spect, false);
            
            }
        
        } else if (msgOut.getAddress() == "/nodejs" && msgOut.getArgAsString(0) == "nodeConnected") {
            
            ofxOscMessage mess;
            mess.setAddress("AMI/master/broadcast");
            mess.addStringArg("Connection established with AMI Master Server");
            Messenger -> sendOSC(mess, true);
        
        } else if (msgOut.getAddress() == "AMI/kinectServer/position") {
            oscduration = msgOut.getArgAsInt32(2);
            kinect_last_update = ofGetFrameNum();
            //Alert -> show("Kinect: "+ofToString(msgOut.getArgAsInt32(0))+","+ofToString(msgOut.getArgAsInt32(1))+","+ofToString(msgOut.getArgAsInt32(2)));
        }
    }
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    ofxOscMessage message;
    
    //Alert -> show(ofToString(key)+" key pressed");
    
    Alert -> show ("Send Message AMI is alive");
    message.setAddress("AMI/is/alive");
    message.addStringArg("<3");
    Messenger -> sendOSC(message,true);
    
    //99: c key
    switch (key) {
        case 99:
            if (calibrating)  {
                calibrating = false;
                Alert -> show("calibration off");
            } else {
                calibrating = true;
                Alert -> show("calibration on");
            }
            break;
        default:
            break;
    }
    
    
}

//--------------------------------------------------------------
void testApp::exit() {
    Alert -> show("exit");
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
