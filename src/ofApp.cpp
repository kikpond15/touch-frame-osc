#include "ofApp.h"
#include <list>

// make a list to keep track of active touches
list <ofTouchEventArgs> touches;

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);
	ofSetFrameRate(60);
	//ofHideCursor();

	// Enable the Windows Touch Hook
	ofxMultitouch::EnableTouch();
	ofAddListener(ofxMultitouch::touchDown, this, &ofApp::touchDown);
	ofAddListener(ofxMultitouch::touchMoved, this, &ofApp::touchMove);
	ofAddListener(ofxMultitouch::touchUp, this, &ofApp::touchUp);

	//GUI SetUP
	parameters.add(hostIpParameter.set("HOST IP", "127.0.0.1"));
	parameters.add(portParameter.set("PORT", "12000"));
	hostIpParameter.addListener(this, &ofApp::onTextChange);
	portParameter.addListener(this, &ofApp::onTextChange);
	gui.setup(parameters);
	gui.add(winWidthLabel.setup("WIDTH", ofToString(ofGetWidth())));
	gui.add(winHeightLabel.setup("HEIHGT", ofToString(ofGetHeight())));

	//OSC SetUP
	host = hostIpParameter.get();
	port = ofToInt(portParameter.get());
	sender.setup(host, port);
}

//--------------------------------------------------------------
void ofApp::update() {
	list<ofTouchEventArgs> ::iterator it;
	ofxOscMessage m, m2;
	std::vector<ofVec3f> pos;

	for (it = touches.begin(); it != touches.end(); ++it) {
		pos.push_back(ofVec3f((*it).x, (*it).y, (*it).id));
	}
	m.setAddress("/touchesLenght");
	m.addIntArg(pos.size());
	ofLogNotice() << "pos.size " << pos.size();
	sender.sendMessage(m);

	for (auto p : pos) {
		m2.setAddress("/touches/position");
		m2.addIntArg(p.x);
		m2.addIntArg(p.y);
		m2.addIntArg(p.z);
	}
	sender.sendMessage(m2);
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Display frame rate
	ofDrawBitmapString(ofToString(roundf(ofGetFrameRate())), 100, 100);

	// Draw circles

	list<ofTouchEventArgs> ::iterator it;
	for (it = touches.begin(); it != touches.end(); ++it) {
		ofSetColor(255, 255, 255, 100);
		ofDrawCircle((*it).x, (*it).y, 20);
		ofSetColor(255, 255, 255, 255);
		ofDrawBitmapString("id: " + ofToString((*it).id), (*it).x, (*it).y);
		ofDrawBitmapString(ofToString((*it).x) + ", " + ofToString((*it).y), (*it).x, (*it).y + 20);
	}
	gui.draw();
}

void ofApp::onTextChange(std::string& text) {
	//ofLogNotice() << "text changed " << text;
	sender.clear();
	host = hostIpParameter.get();
	port = ofToInt(portParameter.get());
	sender.setup(host, port);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	winWidthLabel.setup("WIDTH", ofToString(ofGetWidth()));
	winHeightLabel.setup("HEIHGT", ofToString(ofGetHeight()));
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs& touch) {
	// Add a new circle for this new touch
	touches.push_back(touch);
}

//--------------------------------------------------------------
void ofApp::touchMove(ofTouchEventArgs& touch) {
	// Move the corresponding circle
	std::list <ofTouchEventArgs> ::iterator it;
	for (it = touches.begin(); it != touches.end(); ++it) {
		if (it->id == touch.id) {
			*it = touch;
		}
	}
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs& touch) {
	// Remove the corresponding circle
	ofTouchEventArgs touchToRemove;
	std::list <ofTouchEventArgs> ::iterator it;
	for (it = touches.begin(); it != touches.end(); ++it) {
		if (it->id == touch.id) {
			touchToRemove = *it;
		}
	}
	touches.remove(touchToRemove);
}
