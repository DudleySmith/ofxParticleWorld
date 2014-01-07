#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    m_oWorld.setup();
    
    group.setName("Parameters");
    group.add(m_oWorld.m_pgPartsSettings);
    panel.setup(group);
    panel.ofxBaseGui::setPosition(10, 100);
    
    m_oWorld.currentMode = PARTICLE_ATTRACTOR_MODE_ATTRACT;
    currentModeStr = "1 - PARTICLE_ATTRACTOR_MODE_ATTRACT: attracts to mouse";
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    m_oWorld.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    m_oWorld.drawParticles();
    m_oWorld.drawAttractors();
    m_oWorld.drawEmitters();
    
    panel.draw();
    
    ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == '1'){
		m_oWorld.currentMode = PARTICLE_ATTRACTOR_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_ATTRACTOR_MODE_ATTRACT: attracts to mouse";
	}
	if( key == '2'){
		m_oWorld.currentMode = PARTICLE_ATTRACTOR_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_ATTRACTOR_MODE_REPEL: repels from nearest point";
	}
	if( key == '3'){
		m_oWorld.currentMode = PARTICLE_ATTRACTOR_MODE_NOISE;
		currentModeStr = "3 - PARTICLE_ATTRACTOR_MODE_NOISE: snow particle simulation";
		m_oWorld.resetParticles();
	}
    
	if( key == ' ' ){
		m_oWorld.resetParticles();
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
    
    if(button == OF_MOUSE_BUTTON_LEFT){
        //these are the attraction points used in the forth demo
        m_oWorld.addAttractPoints(ofToString(m_oWorld.m_aAttractors.size()), ofPoint(x, y));
    }

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
