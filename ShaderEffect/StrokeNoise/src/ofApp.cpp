#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(64);
    postProcessFlag = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    snake.update(mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (postProcessFlag) strokeNoise.begin();
    cam.begin();
    snake.draw();
    cam.end();
    if (postProcessFlag)  {
        strokeNoise.end();
        strokeNoise.draw();
    }
    
    strokeNoise.drawUI();
    ofDrawBitmapString("press 'p' to toggle effect", 20, 680);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'p'){
        postProcessFlag = !postProcessFlag;
    }
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
