#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMultitouch.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// add the touch listeners
	void touchDown(ofTouchEventArgs& touch);
	void touchMove(ofTouchEventArgs& touch);
	void touchUp(ofTouchEventArgs& touch);
	void onTextChange(std::string& text);

	ofxPanel gui;
	ofxButton button;
	ofxLabel winWidthLabel;
	ofxLabel winHeightLabel;
	ofParameterGroup parameters;
	ofParameter<std::string> hostIpParameter;
	ofParameter<std::string> portParameter;

	ofxOscSender sender;
	string host;
	int port;
};
