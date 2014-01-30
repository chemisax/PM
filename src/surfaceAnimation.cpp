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
    r = 0;
    speed = 10;
    max_size = sqrt(pow(ofGetHeight(),2.0f)+pow(ofGetWidth(),2.0f));
    
}

bool surfaceAnimation::isPlaying(){
    return playing;
}

void surfaceAnimation::wave_draw(){

    



    int x = ofGetWidth()/2;
    int y = ofGetHeight()/2;


    //外側の波紋の速度が1.0より大なら外側の波紋を
    if(speed > 1.0){
        ofSetColor(255, 255, 255, 255*(speed-3)/3);
        ofCircle(x, y, r);
    
    }
    //外側の波紋の速度が1.5より大なら内側の波紋も
    if(speed > 1.5){
        ofSetColor(0, 0, 0);
        ofCircle(x, y, r*0.9);
    }

    r += speed;
    speed *= friction;

    if (r == max_size/2){
    
        playing = false;
    
    }
}