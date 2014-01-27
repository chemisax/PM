#include "testApp.h"
#include "ofMain.h"
#include "ofxOsc.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(30);
    
    //initialize variables
    calibrating = false;
    
    //Start the alert system
    Alert = new alertSystem(30*2);
    Alert -> show("Welcome to AMI Master <3");
    
    //Start the messenger system
    Messenger = new messenger();
    
    //Start the song
    soundPlayer.loadSound("piensa_en_mi.mp3");
    soundPlayer.setLoop(true);
    soundPlayer.play();
    soundPlayer.setPaused(true);
    
    //initialize kinect
    kinect.setRegistration(true);
    
    kinect.init();
    //kinect.init(true); // shows infrared instead of RGB video image
    //kinect.init(false, false); // disable video image (faster fps)
    kinect.open();
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    //Get new messages and parse them
    updateMessenger();

    //Set background color
    ofBackground(backgroundColor[0], backgroundColor[1], backgroundColor[2]);
    
    //Kinect
    kinect.update();

}

//--------------------------------------------------------------
void testApp::draw() {
    
    //Kinect
    kinect.drawDepth(20, 20, 640, 480);
    
   // Alert -> show(ofToString(kinect.getDistanceAt(200, 200)));
    
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
            
            Alert -> show(msgOut.getArgAsString(0));
            
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
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
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
