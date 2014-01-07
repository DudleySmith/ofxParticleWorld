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
    m_pgPartsSettings.add(m_pxSize.set("Size", 0, 1, 20));
    m_pgPartsSettings.add(m_pxCoefForces.set("Forces", 0, 0, 1));
    m_pgPartsSettings.add(m_pxCoefForces_X.set("ForceX", 0, 0, 1));
    m_pgPartsSettings.add(m_pxCoefForces_Y.set("ForceY", 0, 0, 1));
    m_pgPartsSettings.add(m_pxPulse.set("Pulse", 0, 0, 5));
    m_pgPartsSettings.add(m_pxLifeBase.set("Life", 0, 0, 50));
    m_pgPartsSettings.add(m_pxFriction.set("Friction", 0, 0, 10));
    m_pgPartsSettings.add(m_pxEternalLife.set("IsEternal", 0, 0, 10));

}

//--------------------------------------------------------------
void ofxParticleWorld::resetParticles(){

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&m_aAttractors);;
		p[i].reset();
	}
	
}

//--------------------------------------------------------------
void ofxParticleWorld::update(){
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].update(m_pgPartsSettings);
	}
	
	//lets add a bit of movement to the attract points
    /*
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}	
     */
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
