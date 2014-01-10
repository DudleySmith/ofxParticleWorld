#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    m_oWorld.setup(m_oColorSet);
    m_oColorSet.setup("ColorSets.xml");
    
    // Parts UI --------------------------------------------------------------
    gpParts.add(m_oWorld.m_pgSets);
    uiParts.setup(gpParts);
    uiParts.add(fps.setup("FPS", ""));
    uiParts.setPosition(10, 100);
    uiParts.loadFromFile("Settings.xml");
    
    // Colors UI --------------------------------------------------------------
    gpColors.add(m_oColorSet.m_oUI.m_gGroup);
    uiColors.setup(gpColors);
    uiColors.add(btReload.setup("Reload"));
    uiColors.setPosition(250, 100);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if( m_oWorld.m_pgSets.get(cpxAttract).cast<partAttractorMode>() == PATTRACTOR_ATTRACT){
        currentModeStr = "1 - PATTRACTOR_ATTRACT: attracts";
	}
	if( m_oWorld.m_pgSets.get(cpxAttract).cast<partAttractorMode>() == PATTRACTOR_REPEL){
		currentModeStr = "2 - PATTRACTOR_REPEL: repels";
	}
	if( m_oWorld.m_pgSets.get(cpxAttract).cast<partAttractorMode>() == PATTRACTOR_NOISE){
		currentModeStr = "3 - PATTRACTOR_NOISE: windy";
	}
    
    m_oColorSet.update(btReload);
    
    m_oWorld.update();
    fps = ofToString(ofGetFrameRate());
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    m_oWorld.drawParticles();
    m_oWorld.drawAttractors();
    m_oWorld.drawEmitters();
    
    uiParts.draw();
    uiColors.draw();
    
    ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset.", 10, 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
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
