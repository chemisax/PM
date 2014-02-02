//
//  surface.cpp
//  projectionMappingCube
//
//  Created by José María Campaña Rojas on 23/10/13.
//
//

#include "surface.h"
#include "ofMain.h"

surface::surface (string Name, string imageFile, string xml, float Ws, float Hs) {
    name = Name;
    image = imageFile;
    datafile = xml;
    w = Ws;
    h = Hs;
    showname = false;
    hidden = false;
    vol_interval = 0.1;
    editable = false;
    warper.deactivate();
    
    warper.setup(0,0, w, h);
    warper.load(datafile);
    warper.setCornerSensibility(.05);
    img.loadImage(image);
}

void surface::draw() {
    
    if(!hidden) {
        warper.begin();
        if (editable) warper.draw();
        ofSetColor(255, 255, 255);
        //draw image
        img.draw(0, 0);
        if (showname) ofDrawBitmapString(name,20,20);
        warper.end();
    }
}

void surface::update() {
}

void surface::saveSurf () {
    warper.save(datafile);
}

void surface::setVisibility (bool v) {
    if (!v) {
        hidden = true;
        warper.deactivate();
    } else {
        hidden = false;
        warper.activate();
    }
}

void surface::edit () {
    warper.activate();
    editable = true;
}

void surface::noEdit () {
    warper.deactivate();
    editable = false;
}
