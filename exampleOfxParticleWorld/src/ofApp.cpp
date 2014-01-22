#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    m_oWorld.setup(m_oColorSet);
    m_oColorSet.setup("ColorSets.xml");
    
    // Parts UI --------------------------------------------------------------
    gpParts.add(m_oWorld.m_pgSets);
    uiParts.setup(gpParts);
    uiParts.add(fps.setup("FPS", ""));
    uiParts.add(nbParts.setup("Nb Parts", ""));
    uiParts.add(dist.setup("Distance", ""));
    uiParts.setPosition(10, 100);
    uiParts.loadFromFile("Gigi.xml");
    
    // Colors UI --------------------------------------------------------------
    gpColors.add(m_oColorSet.m_oUI.m_gGroup);
    uiColors.setup(gpColors);
    uiColors.add(btReload.setup("Reload"));
    uiColors.setPosition(250, 100);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(m_oWorld.getPxAttractMode() == PATTRACTOR_ATTRACT){
        currentModeStr = "1 - PATTRACTOR_ATTRACT: attracts";
	}
	if(m_oWorld.getPxAttractMode() == PATTRACTOR_REPEL){
		currentModeStr = "2 - PATTRACTOR_REPEL: repels";
	}
	if(m_oWorld.getPxAttractMode() == PATTRACTOR_NOISE){
		currentModeStr = "3 - PATTRACTOR_NOISE: windy";
	}
    
    m_oColorSet.update(btReload);
    
    m_oWorld.setAttractors(&m_aAttractors);
    m_oWorld.update();
    
    // Emitting
    map<string, ofxEmitter>::iterator oneEmitter;
    for (oneEmitter=m_aEmitters.begin(); oneEmitter!=m_aEmitters.end(); oneEmitter++) {
        (*oneEmitter).second.update();
    }
    
    fps = ofToString(ofGetFrameRate());
    nbParts = ofToString(m_oWorld.m_aParts.size());
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
    
    uiParts.draw();
    uiColors.draw();
    
    ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset.", 10, 20);
    
    //--------------------------------------------------------------
    m_oWorld.draw();
    for(unsigned int i = 0; i < m_aAttractors.size(); i++){
        m_aAttractors[i].draw();
    }
    
    for(unsigned int i = 0; i < m_aEmitters.size(); i++){
        m_aEmitters[ofToString(i)].draw();
    }
    
    //--------------------------------------------------------------
    ofSetColor(ofColor::white);
    vector <ofxAttractor>::iterator oneAttractor;
    for(oneAttractor=m_aAttractors.begin(); oneAttractor!=m_aAttractors.end(); oneAttractor++){
        if(oneAttractor->getType() == CONSTRAINT_LINE){
            ofVec3f distance = oneAttractor->shortDistance(ofPoint(ofGetMouseX(), ofGetMouseY()), true);
            dist = ofToString(distance.length());
            
            ofLine(ofPoint(ofGetMouseX(), ofGetMouseY()), distance + ofPoint(ofGetMouseX(), ofGetMouseY()));
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key==' '){
        m_oWorld.clear();
        m_aEmitters.erase(m_aEmitters.begin(), m_aEmitters.end());
        m_aAttractors.erase(m_aAttractors.begin(), m_aAttractors.end());
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ptStart = ofPoint(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    ptEnd = ofPoint(x,y);
    ofVec3f dist = ptStart - ptEnd;
    
    if(button == OF_MOUSE_BUTTON_LEFT){
        if(ofGetKeyPressed(OF_KEY_LEFT_SHIFT)==true || ofGetKeyPressed(OF_KEY_RIGHT_SHIFT)==true){
            m_aEmitters[ofToString(m_aEmitters.size())] = ofxEmitter(m_oWorld);
        }else{
            if(dist.length() <= 50){
                m_aEmitters[ofToString(m_aEmitters.size())] = ofxEmitter(m_oWorld, ptEnd);
            }else{
                m_aEmitters[ofToString(m_aEmitters.size())] = ofxEmitter(m_oWorld, ptStart, ptEnd);
            }
        }

        
    }else if(button == OF_MOUSE_BUTTON_RIGHT){
        if(dist.length() <= 50){
            m_aAttractors.push_back(ofxAttractor(m_oWorld, ptEnd));
        }else{
            m_aAttractors.push_back(ofxAttractor(m_oWorld, ptStart, ptEnd));
        }
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
