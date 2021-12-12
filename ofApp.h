// Refer to the README.md in the example's root folder for more information on usage

#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "hSlider.h"
#include "bang.h"
#include "toggle.h"
#include "number.h"
#include "hRadio.h"
#include "label.h"

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void touchMoved(int x, int y, int button);
		void touchDown(int x, int y, int button);
		void touchUp(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void toggle_1onMousePressed(bool & e);
		void bang_1onMousePressed(bool & e);	
		void hSlider_1onMousePressed(float & e);
		void number_1onMousePressed(float & e);	
		void hRadio_1onMousePressed(float & e);	
		
		// variables used in the example
		float 	counter;
		bool	bSmooth;
		float color;
		bool bang;
		bool toggle;
		
		class hSlider hSlider_1;
		class bang bang_1;
		class toggle toggle_1;
		class number number_1;
		class hRadio hRadio_1;
		class label label_1;
};
	
