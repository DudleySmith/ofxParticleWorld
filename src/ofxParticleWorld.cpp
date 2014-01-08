#include "ofApp.h"

//--------------------------------------------------------------
void ofxParticleWorld::setup(){
    
    loadSettings();
    
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, ofxParticle());
	
	resetParticles();
}

//--------------------------------------------------------------
void ofxParticleWorld::loadSettings(){
    // Settings ---------------
    m_pgPartsSettings.setName("Parts settings");
    m_pgPartsSettings.add(m_pxSize.set(cpxSize, 0, 1, 20));
    m_pgPartsSettings.add(m_pxRateSize.set(cpxRateSize, 0, 0, 1));
    
    m_pgPartsSettings.add(m_pxCoefForces.set(cpxCoefForces, 0.4, 0, 2));
    m_pgPartsSettings.add(m_pxCoefForcesMin.set(cpxCoefForcesMin, 0.05, 0, 0.1));
    m_pgPartsSettings.add(m_pxCoefForces_X.set(cpxCoefForces_X, 0, 0, 1));
    m_pgPartsSettings.add(m_pxCoefForces_Y.set(cpxCoefForces_Y, 0, 0, 1));
    m_pgPartsSettings.add(m_pxPulse.set(cpxPulse, 0, 0, 5));
    m_pgPartsSettings.add(m_pxDrag.set(cpxDrag, 0.5, 0, 1));
    m_pgPartsSettings.add(m_pxDistMin.set(cpxDistMin, 40, 0, 250));
    m_pgPartsSettings.add(m_pxDistMax.set(cpxDistMax, 300, 0, 1000));
    m_pgPartsSettings.add(m_pxVelMax.set(cpxVelMax, 1, 0, 100));
    
    m_pgPartsSettings.add(m_pxLifeBase.set(cpxLifeBase, 0.5, 0, 1));
    m_pgPartsSettings.add(m_pxEternalLife.set(cpxEternalLife, 0, 0, 10));

}

//--------------------------------------------------------------
void ofxParticleWorld::resetParticles(){

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&m_aAttractors);
        
        ofVec3f originVel;
        originVel.x = ofRandom(-1*m_pxPulse, m_pxPulse);
        originVel.y = ofRandom(-1*m_pxPulse, m_pxPulse);
        
		p[i].reset(originVel);
	}
	
}

//--------------------------------------------------------------
void ofxParticleWorld::update(){
    
    vector<ofxParticle>::iterator   oneParticle;
    
    for(oneParticle = p.begin(); oneParticle != p.end(); oneParticle++){
        (*oneParticle).setMode(currentMode);
		(*oneParticle).update(m_pgPartsSettings);
	}
    
}

//--------------------------------------------------------------
void ofxParticleWorld::drawParticles(){
    
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
	}
	
}

//--------------------------------------------------------------
void ofxParticleWorld::drawAttractors(){
    
    ofSetColor(ofColor::red);
    
    if( currentMode == PARTICLE_ATTRACTOR_MODE_ATTRACT || currentMode == PARTICLE_ATTRACTOR_MODE_REPEL){
        for(unsigned int i = 0; i < m_aAttractors.size(); i++){
            ofNoFill();
            ofCircle(m_aAttractors[i].getPos(), 10);
            ofFill();
            ofCircle(m_aAttractors[i].getPos(), 4);
        }
    }
    
}

//--------------------------------------------------------------
void ofxParticleWorld::drawEmitters(){
    
    ofSetColor(ofColor::green);
    
    for(unsigned int i = 0; i < m_aEmitters.size(); i++){
        ofNoFill();
        ofCircle(m_aEmitters[i].getPos(), 10);
        ofFill();
        ofCircle(m_aEmitters[i].getPos(), 4);
    }
    
}

//--------------------------------------------------------------
void ofxParticleWorld::addAttractPoints(string _name, ofPoint _pos){
    
    ofxAttractor attractorToAdd;
    attractorToAdd.setPos(_pos);
    
    m_aAttractors.push_back(attractorToAdd);
    
}


/*
//--------------------------------------------------------------
void ofxParticleWorld::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofxParticleWorld::keyReleased(int key){

}

//--------------------------------------------------------------
void ofxParticleWorld::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofxParticleWorld::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxParticleWorld::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxParticleWorld::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofxParticleWorld::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofxParticleWorld::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofxParticleWorld::dragEvent(ofDragInfo dragInfo){

}
*/
