#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){
    
    //Normal size is 1024x768x2
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new testApp());
    
}
