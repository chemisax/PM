#include "testApp.h"
#include "ofMain.h"
#include "ofxOsc.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFullscreen(true);
    
    ofSetFrameRate(30);
    
    calibrating = false;
    
    //Start the alert system
    Alert = new alertSystem(30*2);
    Alert -> show("Welcome to AMI Master <3");
    
    //Start the messenger system
    Messenger = new messenger();
    
    //Start the sound
    soundPlayer.loadSound("hb.mp3");
    soundPlayer.setVolume(.3);
    
    //BPM & Timers
    soundDuration = 4;
    defaultRate = 60;
    rateCounter = 0;
    beat_rate = defaultRate;
    heikin_update_rate = 10;
    heikin_update_current = 0;
    longestDistance = 450;
    heikin_counter = 0;
    oscduration = 0;
    kinect_last_update = 0;
    kinect_tolerance = 30;
    for (int i=0; i<3; i++) heikin[i] = defaultRate;
    ami_yonda = false;
    
    waveMsg.setAddress("AMI/master/screen1/command/wave");
    waveMsg.addStringArg("play");
    
    //Create AMI warp container
    amiSurface = new surface("AMI", "ami.png", "ami_calibration.xml",200,647);
    amiSurface -> edit();
    
    calibration.loadImage("calibration.png");
    line_counter = 0;
    ami_alpha = 255;
    frame_counter_ami = 0;
    
    /*
    mylist.push_back(new alertSystem(30*2));
    
    itr = mylist.begin();
    
    for(itr = mylist.begin() ; itr != mylist.end() ; itr ++){
    }
    
    if ( ! (*itr) -> show("hey") ) {
        mylist.erase(itr);
    }
    */
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    //Set background color
    ofBackground(backgroundColor[0], backgroundColor[1], backgroundColor[2]);
    
    //Get new messages and parse them
    updateMessenger();
    
    //RateCounter
    update_bpm();
    
    //play heartbeat/call line
    heartBeat();
    
    //Update AMI
    amiSurface -> update();
    
    Alert -> show(ofToString((float)beat_rate/(float)defaultRate));
}

//--------------------------------------------------------------
void testApp::draw() {
    
    //Draw calibration lines if calibrating
    drawCalibrationLines();
    
    //Draw line animations
    Lines();
    
    //Draw Ami
    ami_draw();
    
    //Draw mask
    calibration.draw(0,0);
    
    // Write alerts if available
    Alert -> draw();

}

//--------------------------------------------------------------
void testApp::Lines () {
    //Call the draw Method
    for(itr = lines.begin() ; itr != lines.end() ; itr ++) (*itr) -> line_draw();
    
    //Delete lines that are no longer being displayed
    for(itr = lines.begin() ; itr != lines.end() ; itr ++) {
        if (!(*itr) -> isPlaying()) {
            Messenger -> sendOSC(waveMsg, false);
            lines.erase(itr);
        }
    }
}

//--------------------------------------------------------------
void testApp::heartBeat () {
    if (rateCounter >= (int) beat_rate) {
        ofxOscMessage msg;
        rateCounter = 0;
        soundPlayer.play();
        line_counter ++;
        lines.push_back(new screenAnimation(255,255,255,ofRandom(1,30),20));
        msg.setAddress("AMI/master/bpm");
        msg.addIntArg(beat_rate);
        Messenger -> sendOSC(msg, true);
    } else {
        rateCounter ++;
    }
}

//--------------------------------------------------------------
void testApp::update_bpm() {
    if ((ofGetFrameNum()-kinect_last_update) <= kinect_tolerance) {
        if (heikin_update_current == heikin_update_rate) {
            heikin_update_current = 0;
            heikin[heikin_counter] = oscduration;
            if (heikin_counter == 3) {
                heikin_counter = 0;
                rate = ((float)((heikin[0]+heikin[1]+heikin[2])/3)/longestDistance)*defaultRate;
                beat_rate = ((int)rate > soundDuration) ? rate : soundDuration+1;
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
            if (msgOut.getArgAsString(0) == "status") {
                ofxOscMessage mess;
                mess.setAddress("AMI/master/broadcast/status");
                mess.addStringArg("AMI Master/Server is online");
                Messenger -> sendOSC(mess, true);
            }
        } else if (msgOut.getAddress() == "/nodejs" && msgOut.getArgAsString(0) == "nodeConnected") {
            ofxOscMessage mess;
            mess.setAddress("AMI/master/broadcast");
            mess.addStringArg("Connection established with AMI Master Server");
            Messenger -> sendOSC(mess, true);
        } else if (msgOut.getAddress() == "AMI/kinectServer/position") {
            oscduration = msgOut.getArgAsInt32(2);
            kinect_last_update = ofGetFrameNum();
        }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    ofxOscMessage message;
    Alert -> show(ofToString(key)+" key pressed");
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
        case 115:
            Alert -> show("saved");
            amiSurface -> saveSurf();
            break;
        default:
            break;
    }
}

void testApp::ami_draw() {
    
    if (beat_rate/defaultRate < 0.2 && line_counter > 14) {
        if (!ami_yonda) {
            ami_yonda = true;
            ofxOscMessage mensaje;
            mensaje.setAddress("AMI/master/order/ami_dasu");
            mensaje.addStringArg("true");
            Messenger -> sendOSC(mensaje, false);
        }
        
        frame_counter_ami ++;
        
        if (frame_counter_ami <= 8) ami_alpha = 255*((float)frame_counter_ami/8);
        
        if (frame_counter_ami > 8) ami_alpha = 255;
        
        ofSetColor(255, 255, 255,ami_alpha);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        amiSurface -> draw();
        
        if (frame_counter_ami == 30) frameCounter = 0;
        if (frame_counter_ami > 31) {
            frameCounter ++;
            ami_alpha = 255-(255*((float)frameCounter/30));
        }
        
        if (frameCounter == 30) {
            frameCounter = 0;
            line_counter = 0;
            ami_alpha = 255;
            frame_counter_ami = 0;
            ami_yonda = false;
        }
        ofSetColor(0, 0, 0);
    } else if (calibrating) {
        ofSetColor(255, 0, 0);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        amiSurface -> draw();

    } else {
        frameCounter = 0;
        line_counter = 0;
        ami_alpha = 255;
        frame_counter_ami = 0;
        ami_yonda = false;
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
