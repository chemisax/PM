#include "testApp.h"
#include "ofMain.h"
#include "ofxOsc.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(30);
    
    //Start the alert system
    Alert = new alertSystem(30*3);
    Alert -> show("Welcome to AMI Server <3");
    
    //Start the messenger system
    Messenger = new messenger();
}

//--------------------------------------------------------------
void testApp::update(){
    
    //Respond to incoming messages
    string messenger_status = Messenger -> update();
    if (messenger_status != "-1") Alert -> show(messenger_status);
    
    ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void testApp::draw() {
    // Calls for classes that write to the screen
    Alert -> draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    ofxOscMessage message;
    message.setAddress("of/test/message");
    message.addIntArg(123);
    Messenger -> sendOSC(message);
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
