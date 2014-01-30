//
//  screenAnimation.cpp
//  Animation
//
//  Created by Yuki Furugori on 2014/01/30.
//
//

#include "screenAnimation.h"
#include "ofMain.h"

screenAnimation::screenAnimation(int color_R, int color_G,int color_B, int line_width2 , int anim_duration2){
   
    color[0] = color_R;
    color[1] = color_G;
    color[2] = color_B;
    line_width = line_width2;
    anim_duration = anim_duration2;
    
    animation_counter = 0;
    fade_start = anim_duration * 0.8;
    
    playing = true;
    
}

bool screenAnimation::isPlaying() {
    return playing;
}

void screenAnimation::line_draw(){

    
    if (animation_counter <= anim_duration) {
        float alpha = (animation_counter >= fade_start) ? 255*((float)((anim_duration-animation_counter)*100/(anim_duration-fade_start))/100) : 255;
        int y = (ofGetHeight()/anim_duration)*animation_counter;
        ofSetColor(color[0],color[1],color[2], alpha);
        
    /*
    case1:*/
        ofRect(0, y, ofGetWidth(), line_width);
    /*case2:
        ~~
    case3:
        ----
    */
        animation_counter ++;
    } else {
        playing = false;
    }
    
    
    
    /*
    //ラインが上から下までいったらカウンターをリセット
    else{
        animation_counter = 0;
    }*/
    
    /*
     a--;
     a %= b ;
     
     for (int i=a; i<ofGetHeight(); i+=b) {
     ofLine(0, i, ofGetWidth(), i) ;
     ofRect(x, y, ofGetWidth(), stroke);
     }*/

    
}