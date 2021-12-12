// Refer to the README.md in the example's root folder for more information on usage

#include "ofApp.h"
#include "emscripten.h"
#include "emscripten/bind.h"

using namespace emscripten;

	int inChannel;
	int inPitch;
	int inVelocity;
	int outChannel;
	int outPitch;
	int outVelocity;
	
void midiIn(std::string ev) {
	unsigned char* uEv = (unsigned char*)ev.c_str();
	inChannel= uEv[0];
	inPitch= uEv[1];
	inVelocity= uEv[2];
}

EMSCRIPTEN_BINDINGS(Module) {
	emscripten::function("midiIn", &midiIn);
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofAddListener(toggle_1.onMousePressed, this, &ofApp::toggle_1onMousePressed);
	ofAddListener(bang_1.onMousePressed, this, &ofApp::bang_1onMousePressed);
	ofAddListener(hSlider_1.onMousePressed, this, &ofApp::hSlider_1onMousePressed);
	ofAddListener(number_1.onMousePressed, this, &ofApp::number_1onMousePressed);
	ofAddListener(hRadio_1.onMousePressed, this, &ofApp::hRadio_1onMousePressed);
	hSlider_1.setup(100, 100, 200, 20, 0, 1000);
	number_1.setup(100, 150, 100, 20, 0, 1000);
	bang_1.setup(200, 200, 20);
	toggle_1.setup(250, 200, 40);
	hRadio_1.setup(100, 300, 20, 8);
	label_1.setup(300, 300, 100, 20, "OF GUI");
	inChannel = 0;
	inPitch = 0;
	inVelocity = 0;
	outChannel = 0;
	outPitch = 0;
	outVelocity = 0;
	counter = 0;
	ofSetCircleResolution(50);
	ofBackground(255,255,255);
	bSmooth = false;
	ofSetWindowTitle("graphics example");
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
}

//--------------------------------------------------------------
void ofApp::update(){
	// update event slowly increments the counter variable
	counter = counter + 0.033f;
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofDrawBitmapString("midiIn: " + ofToString(inChannel) + ", " + ofToString(inPitch) + ", " + ofToString(inVelocity), 20, 20);
	ofDrawBitmapString("midiOut: " + ofToString(outChannel) + ", " + ofToString(outPitch) + ", " + ofToString(outVelocity), 20, 50);
	
	//--------------------------- circles
	//let's draw a circle:
	ofSetColor(color,130,0);
	float radius = 50 + 10 * sin(counter);
	ofFill();		// draw "filled shapes"
	ofDrawCircle(100,400,radius);

	// now just an outline
	ofNoFill();
	ofSetHexColor(0xCCCCCC);
	ofDrawCircle(100,400,80);

	// use the bitMap type
	// note, this can be slow on some graphics cards
	// because it is using glDrawPixels which varies in
	// speed from system to system.  try using ofTrueTypeFont
	// if this bitMap type slows you down.
	ofSetHexColor(0x000000);
	ofDrawBitmapString("circle", 75,500);


	//--------------------------- rectangles
	ofFill();
	for (int i = 0; i < 200; i++){
		ofSetColor((int)ofRandom(0,255),(int)ofRandom(0,255),(int)ofRandom(0,255));
		ofDrawRectangle(ofRandom(250,350),ofRandom(350,450),ofRandom(10,20),ofRandom(10,20));
	}
	ofSetHexColor(0x000000);
	ofDrawBitmapString("rectangles", 275,500);

	//---------------------------  transparency
	ofSetHexColor(0x00FF33);
	ofDrawRectangle(400,350,100,100);
	// alpha is usually turned off - for speed puposes.  let's turn it on!
	ofEnableAlphaBlending();
	ofSetColor(255,0,0,127);   // red, 50% transparent
	ofDrawRectangle(450,430,100,33);
	ofSetColor(255,0,0,(int)(counter * 10.0f) % 255);   // red, variable transparent
	ofDrawRectangle(450,370,100,33);
	ofDisableAlphaBlending();

	ofSetHexColor(0x000000);
	ofDrawBitmapString("transparency", 410,500);

	//---------------------------  lines
	// a bunch of red lines, make them smooth if the flag is set

	ofSetHexColor(0xFF0000);
	for (int i = 0; i < 20; i++){
		ofDrawLine(600,300 + (i*5),800, 250 + (i*10));
	}

	ofSetHexColor(0x000000);
	ofDrawBitmapString("lines\npress 's' to toggle smoothness", 600,500);
	hSlider_1.draw();
	bang_1.draw();
	toggle_1.draw();
	number_1.draw();
	hRadio_1.draw();
	label_1.draw();
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
	// the key of s toggles antialiasing
	if (key == 's'){
		bSmooth = !bSmooth;
        if (bSmooth){
            ofEnableAntiAliasing(); 
        }else{
            ofDisableAntiAliasing(); 
        }
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::toggle_1onMousePressed(bool & e){
ofLog(OF_LOG_NOTICE, "toggle " + ofToString(e));
	toggle = e;
}

//--------------------------------------------------------------
void ofApp::bang_1onMousePressed(bool & e){
ofLog(OF_LOG_NOTICE, "bang " + ofToString(e));
	bang = e;
}

//--------------------------------------------------------------
void ofApp::hSlider_1onMousePressed(float & e){
ofLog(OF_LOG_NOTICE, "slider " + ofToString(e));
	color = e;
}

//--------------------------------------------------------------
void ofApp::number_1onMousePressed(float & e){
ofLog(OF_LOG_NOTICE, "number " + ofToString(e));
}

//--------------------------------------------------------------
void ofApp::hRadio_1onMousePressed(float & e){
ofLog(OF_LOG_NOTICE, "hRadio " + ofToString(e));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	outChannel = 144;
	outPitch = 52;
	outVelocity = 32;
	int array[3] = {outChannel, outPitch, outVelocity};
	size_t lengthOfArray = sizeof array / sizeof array[0];
	EM_ASM_(
	var data = new Uint32Array(HEAPU32.buffer, $0, $1);
	window["setMidiOut"] = data, array, lengthOfArray);
	}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	outChannel = 128;
	outPitch = 52;
	outVelocity = 32;
	int array[3] = {outChannel, outPitch, outVelocity};
	size_t lengthOfArray = sizeof array / sizeof array[0];
	EM_ASM_(
	var data = new Uint32Array(HEAPU32.buffer, $0, $1);
	window["setMidiOut"] = data, array, lengthOfArray);
	}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::touchDown(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::touchMoved(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::touchUp(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
