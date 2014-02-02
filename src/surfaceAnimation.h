//
//  surfaceAnimation.h
//  Animetion
//
//  Created by Yuki Furugori on 2014/01/30.
//
//

#ifndef __Animetion__surfaceAnimation__
#define __Animetion__surfaceAnimation__

#include <iostream>

#endif /* defined(__Animetion__surfaceAnimation__) */

#pragma once

class surfaceAnimation {
    
public:
    
    surfaceAnimation(int color_R, int color_G, int color_B);
    void wave_draw();
    bool isPlaying();
    
private:
    int color[3];
    float friction,ra,speed,max_size;
    bool playing;
    
};
