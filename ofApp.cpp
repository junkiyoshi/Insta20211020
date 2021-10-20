#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.45);

	ofNoFill();
	auto len = 300;
	for (int i = 0; i < 8; i++) {

		if (i < 4) {

			ofRotateX(90);
		}
		else if (i < 5) {

			ofRotateY(90);
		}
		else {

			ofRotateY(180);
		}

		for (int k = 0; k < 30; k++) {

			auto location = glm::vec3(ofRandom(-len * 0.5, len * 0.5), ofRandom(-len * 0.5, len * 0.5), len * 0.5);
			auto radius = (int)(ofRandom(1000) + ofGetFrameNum()) % 150 - 100;

			if (radius < 0) {

				auto z = ofMap(radius, -100, 0, len * 10, 0);
				ofDrawLine(location + glm::vec3(0, 0, z), location + glm::vec3(0, 0, z + 50));
			}
			else {

				ofSetColor(255, radius > 25 ? ofMap(radius, 25, 50, 255, 0) : 255);

				ofBeginShape();
				for (int deg = 0; deg < 360; deg++) {

					auto vertex = location + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));

					if (vertex.y > len * 0.5) { vertex.y = len * 0.5; }
					if (vertex.y < -len * 0.5) { vertex.y = -len * 0.5; }
					if (vertex.x > len * 0.5) { vertex.x = len * 0.5; }
					if (vertex.x < -len * 0.5) { vertex.x = -len * 0.5; }

					ofVertex(vertex);
				}
				ofEndShape(true);
			}
		}
	}

	ofFill();
	ofSetColor(0);

	ofDrawBox(len * 0.75);

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}