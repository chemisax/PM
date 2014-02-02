//
//  messenger.h
//  AMI
//
//  Created by José María Campaña Rojas on 23/01/14.
//
//

#ifndef __AMI__messenger__
#define __AMI__messenger__

#include <iostream>
#include "ofxOsc.h"

#define LIST_PORT 9999
#define SEND_PORT 9998  //slave app
#define SEND_PORT2 8080 //node.js
#define HOST "192.168.1.6" //192.168.1.82
#define HOST_2 "localhost"

#endif /* defined(__AMI__messenger__) */

#pragma once

class messenger {
public:
    messenger();
    void sendOSC(ofxOscMessage message, bool sendToNodeJS);
    ofxOscMessage update();
private:
    ofxOscReceiver receiver;
    ofxOscSender sender;
    ofxOscSender senderNode;
    ofxOscMessage emptyMessage;
    
    string dumpOSC(ofxOscMessage m);
};