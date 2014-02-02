//
//  surfaceAnimation.cpp
//  Animetion
//
//  Created by Yuki Furugori on 2014/01/30.
//
//

#include "surfaceAnimation.h"
#include "ofMain.h"


surfaceAnimation::surfaceAnimation(int color_R, int color_G, int color_B){
    
    color[0] = color_R;
    color[1] = color_G;
    color[2] = color_B;
    
    friction = 0.985; //減衰率
    ra = 0;
    speed =8;
    max_size = sqrt(pow(ofGetHeight(),2.0f)+pow(ofGetWidth(),2.0f));
    
    playing = true;
    
}

bool surfaceAnimation::isPlaying(){
    return playing;
}

void surfaceAnimation::wave_draw(){


    int x = ofGetWidth()/2;
    int y = ofGetHeight()/2;


    //外側の波紋の速度が1.0より大なら外側の波紋を
    /*
    if(speed > 1.0){
        ofSetColor(255, 255, 255, 255*(speed-3)/3);
        ofCircle(x, y, r);
    
    }
    //外側の波紋の速度が1.5より大なら内側の波紋も
    if(speed > 1.5){
        ofSetColor(0, 0, 0);
        ofCircle(x, y, r*0.9);
    }
     */
    
    if(speed > 0.02){
        ofBeginShape();
        ofSetColor(255, 255, 255, 100*(speed-3)/3);
        for(float i = 0; i< TWO_PI; i+=0.01*HALF_PI*0.5){
            float r = (2-2*sin(i) +sin(i)*sqrt(abs(cos(i)))/(sin(i)+1.4))*-ra*2;
            float x = ofGetWidth()/2 +cos(i) * r;
            float y = ofGetHeight()/2 +sin(i) * r;
            ofVertex(x, y+100-ra);
        }
        ofEndShape();
    }
    
    if(speed > 0.05){
        ofBeginShape();
        ofSetColor(0, 0, 0);
        for(float i = 0; i< TWO_PI; i+=0.01*HALF_PI*0.5){
            float r = (2-2*sin(i) +sin(i)*sqrt(abs(cos(i)))/(sin(i)+1.4))*-ra*0.75*2;
            float x = ofGetWidth()/2 +cos(i) * r;
            float y = ofGetHeight()/2 +sin(i) * r;
            ofVertex(x, y+130-ra);
        }
        ofEndShape();
    }
    
    ra += speed;
    speed *= friction;

    if (ra == max_size/2){
    
        playing = false;
    
    }
}