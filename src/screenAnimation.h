//
//  screenAnimation.h
//  Animation
//
//  Created by Yuki Furugori on 2014/01/30.
//
//

#ifndef __Animation__screenAnimation__
#define __Animation__screenAnimation__

#include <iostream>

#endif /* defined(__Animation__screenAnimation__) */


#pragma once

class screenAnimation {
  
public:
    
    void line_draw();
    
    screenAnimation(int color_R,int color_G,int color_B ,int line_width2 , int anim_duration2);
    bool isPlaying();
private:
    
    int color[3],line_width,anim_duration,animation_counter,fade_start;
    bool playing;

};