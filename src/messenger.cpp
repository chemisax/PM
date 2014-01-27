//
//  messenger.cpp
//  AMI
//
//  Created by José María Campaña Rojas on 23/01/14.
//
//

#include "messenger.h"
#include "ofMain.h"

messenger::messenger() {
    ofLog(OF_LOG_NOTICE, "Messenger started");
    ofLog(OF_LOG_NOTICE, " >Messenger can just receive messages");
    receiver.setup(LIST_PORT);
    sender.setup(HOST, SEND_PORT);
}
string messenger::update() {
    while(receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        ofLog(OF_LOG_NOTICE, "incoming message");
        return dumpOSC(m);
    }
    return "-1";
}

void messenger::sendOSC(ofxOscMessage message) {
    sender.sendMessage(message);
}
void messenger::messageReceived() {
    ofLog(OF_LOG_NOTICE, "Message Received");
}

string messenger::dumpOSC(ofxOscMessage m) {
    string msg_string;
    msg_string = m.getAddress();
    for (int i=0; i<m.getNumArgs(); i++ ) {
        msg_string += " ";
        if(m.getArgType(i) == OFXOSC_TYPE_INT32)
            msg_string += ofToString( m.getArgAsInt32(i));
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT)
            msg_string += ofToString( m.getArgAsFloat(i));
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING)
            msg_string += m.getArgAsString(i);
    }
    return msg_string;
    //cout << msg_string << endl;
}