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
#define SEND_PORT 9998
#define HOST "localhost"

#endif /* defined(__AMI__messenger__) */

#pragma once

class messenger {
public:
    messenger();
    void sendOSC(ofxOscMessage message);
    
    string update();
private:
    ofxOscReceiver receiver;
    ofxOscSender sender;
    
    void messageReceived();
    string dumpOSC(ofxOscMessage m);
};