//
//  surface.h
//  projectionMappingCube
//
//  Created by José María Campaña Rojas on 23/10/13.
//
//

#ifndef __projectionMappingCube__surface__
#define __projectionMappingCube__surface__

#include <iostream>
#include "ofMain.h"
#include "ofxGLWarper.h"


#endif /* defined(__projectionMappingCube__surface__) */

#pragma once

class surface {
private:
    float w,h,volume,vol_interval;
    string name, image, datafile;
    bool showname, hidden, editable;
    ofxGLWarper warper;
    ofImage img;
    
public:
    surface(string Name, string imageFile, string xml, float Ws, float Hs);
    void draw();
    void update();
    void saveSurf();
    void setVisibility(bool v);
    void edit();
    void noEdit();
};