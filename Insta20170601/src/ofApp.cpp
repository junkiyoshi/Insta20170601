#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
	for (ofxBulletBox* tmp : this->obs) { delete tmp; }
	this->obs.clear();

	for (ofxBulletBox* tmp : this->boxes) { delete tmp; }
	this->boxes.clear();
}


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("born box");
	ofSetFrameRate(30);
	ofBackground(255);
	ofEnableDepthTest();

	this->world.setup();
	this->world.setGravity(ofVec3f(0.0, -1024.0, 0));

	ofxBulletBox* obstacle = new ofxBulletBox();
	obstacle->create(this->world.world, ofVec3f(0, -ofGetHeight(), -512), 0.0f, 4096, 64, 4096);
	obstacle->setProperties(1.0, 0.3);
	obstacle->add();
	this->obs.push_back(obstacle);

}

//--------------------------------------------------------------
void ofApp::update(){
	if (ofGetFrameNum() % (30 * 3) == 1) {
		float size = 30;
		int len = 5;
		float noise_param = 0.05;
		for (int x = -size * len; x < size * len; x += size) {
			for (int y = -size * len; y < size * len; y += size) {
				for (int z = -size * len; z < size * len; z += size) {
					if (ofNoise(x / size * noise_param, y / size * noise_param, z / size * noise_param, ofGetFrameNum() * noise_param) > 0.5) {
						ofxBulletBox* box = new ofxBulletBox();
						box->create(this->world.world, ofVec3f(x, y + ofGetHeight() / 2, z), 1.0, size, size, size);
						box->setRestitution(1.0);
						box->add();

						this->boxes.push_back(box);

						ofColor color;
						color.setHsb(ofRandom(255), 255, 255);
						this->boxes_colors.push_back(color);
						this->boxes_life.push_back(255);
					}
				}
			}
		}
	}

	this->world.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	this->cam.begin();

	ofRotateY(ofGetFrameNum() % 360);

	ofEnableLighting();
	this->light.setPosition(this->cam.getPosition());
	this->light.enable();

	float size = 30;
	int len = 5;
	ofNoFill();
	ofSetColor(0, 8);
	for (int x = -size * len; x < size * len; x += size) {
		for (int y = -size * len; y < size * len; y += size) {
			for (int z = -size * len; z < size * len; z += size) {
				ofBox(ofVec3f(x, y + ofGetHeight() / 2, z), size);
			}
		}
	}

	ofFill();
	for (int i = 0; i < this->obs.size(); i++) {
		ofSetColor(128);
		this->obs[i]->draw();
	}

	for (int i = 0; i < this->boxes.size(); i++) {
		ofSetColor(this->boxes_colors[i], this->boxes_life[i]);
		this->boxes[i]->draw();
	}

	vector<int> removeIndexes = {};
	for (int i = 0; i < this->boxes.size(); i++) {
		this->boxes_life[i] -= 2;
		if (this->boxes_life[i] < 0) {
			this->boxes[i]->remove();
			removeIndexes.push_back(i);
		}
	}

	for (int i = removeIndexes.size() - 1; i > -1; i--) {
		this->boxes_life.erase(this->boxes_life.begin() + removeIndexes[i]);
		this->boxes_colors.erase(this->boxes_colors.begin() + removeIndexes[i]);
		this->boxes.erase(this->boxes.begin() + removeIndexes[i]);
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
