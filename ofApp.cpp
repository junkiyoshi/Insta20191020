#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofRandom(100) < 4) {

		auto ripple = make_unique<Ripple>(glm::vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
		this->ripple_list.push_back(move(ripple));
	}

	for (auto& ripple : this->ripple_list) {

		ripple->update();
	}

	for (int i = this->ripple_list.size() - 1; i >= 0; i--) {

		if (this->ripple_list[i]->isDead()) {

			this->ripple_list.erase(this->ripple_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (auto& ripple : this->ripple_list) {

		ripple->draw();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}