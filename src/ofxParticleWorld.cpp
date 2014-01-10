#include "ofApp.h"

//--------------------------------------------------------------
void ofxParticleWorld::setup(ofxColorSet& _colorSet){
    
    m_pColorSet = &_colorSet;
    
    loadSettings();
    
	int num = 1500;
	m_aParts.assign(num, ofxParticle());
	
	resetParticles();
    
}

//--------------------------------------------------------------
void ofxParticleWorld::loadSettings(){
    
    // Settings ---------------
    m_pgSets.setName("Parts settings");
    m_pgSets.add(m_pxRenderMode.set(cpxRender, 0, PRENDER_NoRender, PRENDER_OBLIQU));
    m_pgSets.add(m_pxAttractMode.set(cpxAttract, 0, PATTRACTOR_ATTRACT, PATTRACTOR_NOISE));
    
    m_pgSets.add(m_pxSize.set(cpxSize, 0, 1, 20));
    m_pgSets.add(m_pxRateSize.set(cpxRateSize, 0, 0, 1));
    
    m_pgSets.add(m_pxCoefForces.set(cpxCoefForces, 0.4, 0, 2));
    m_pgSets.add(m_pxCoefForcesMin.set(cpxCoefForcesMin, 0.05, 0, 0.1));
    m_pgSets.add(m_pxCoefForces_X.set(cpxCoefForces_X, 0, 0, 1));
    m_pgSets.add(m_pxCoefForces_Y.set(cpxCoefForces_Y, 0, 0, 1));
    m_pgSets.add(m_pxPulse.set(cpxPulse, 0.5, 0, 5));
    m_pgSets.add(m_pxDrag.set(cpxDrag, 0.5, 0, 1));
    m_pgSets.add(m_pxDistMin.set(cpxDistMin, 40, 0, 250));
    m_pgSets.add(m_pxDistMax.set(cpxDistMax, 300, 0, 1000));
    m_pgSets.add(m_pxVelMax.set(cpxVelMax, 1, 0, 100));
    
    m_pgSets.add(m_pxLifeBase.set(cpxLifeBase, 0.5, 0, 1));
    m_pgSets.add(m_pxEternalLife.set(cpxEternalLife, 0, 0, 10));

}

//--------------------------------------------------------------
void ofxParticleWorld::resetParticles(){

	vector<ofxParticle>::iterator   oneParticle;
    
    for(oneParticle = m_aParts.begin(); oneParticle != m_aParts.end(); oneParticle++){
    	(*oneParticle).setAttractPoints(&m_aAttractors);
        
        ofVec3f originVel;
        originVel.x = ofRandom(-1*m_pxPulse, m_pxPulse);
        originVel.y = ofRandom(-1*m_pxPulse, m_pxPulse);
        
		(*oneParticle).reset(originVel);
	}
	
}

//--------------------------------------------------------------
void ofxParticleWorld::update(){
    
    vector<ofxParticle>::iterator   oneParticle;
    
    for(oneParticle = m_aParts.begin(); oneParticle != m_aParts.end(); oneParticle++){
        (*oneParticle).update(m_pgSets);
	}
    
}

//--------------------------------------------------------------
void ofxParticleWorld::drawParticles(){
    
    vector<ofxParticle>::iterator   oneParticle;
    ofColor                         colorToDraw;
    int                             idxPart = 0;
    
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	
    for(oneParticle = m_aParts.begin(); oneParticle != m_aParts.end(); oneParticle++){
        float gradientProgress = (float)idxPart/(float)m_aParts.size();
        
        colorToDraw = m_pColorSet->getCurrentSetByProgress(gradientProgress);
        idxPart++;
        
        (*oneParticle).setColor(colorToDraw);
    	(*oneParticle).draw();
	}
    

    

	
}

//--------------------------------------------------------------
void ofxParticleWorld::drawAttractors(){
    
    ofSetColor(ofColor::red);
    
    for(unsigned int i = 0; i < m_aAttractors.size(); i++){
        ofNoFill();
        ofCircle(m_aAttractors[i].getPos(), 10);
        ofFill();
        ofCircle(m_aAttractors[i].getPos(), 4);
    }
    
}

//--------------------------------------------------------------
void ofxParticleWorld::drawEmitters(){
    
    ofSetColor(ofColor::blue);
    
    for(unsigned int i = 0; i < m_aEmitters.size(); i++){
        m_aEmitters[ofToString(i)].draw();
    }
    
}

//--------------------------------------------------------------
void ofxParticleWorld::addAttractPoints(string _name, ofPoint _pos){
    
    ofxAttractor attractorToAdd;
    attractorToAdd.setPos(_pos);
    
    m_aAttractors.push_back(attractorToAdd);
    
}

//--------------------------------------------------------------
void ofxParticleWorld::addEmitterRandom(string _name){
    ofxEmitter emitterToAdd;
    
    emitterToAdd.setEmitType(EMIT_RANDOM);
    m_aEmitters[_name] = emitterToAdd;
}

//--------------------------------------------------------------
void ofxParticleWorld::addEmitterPoint(string _name, ofPoint _p1){
    ofxEmitter emitterToAdd;
    
    emitterToAdd.setEmitType(EMIT_POINT);
    emitterToAdd.setPoint(_p1);
    m_aEmitters[_name] = emitterToAdd;
}

//--------------------------------------------------------------
void ofxParticleWorld::addEmitterLine(string _name, ofPoint _p1, ofPoint _p2){
    ofxEmitter emitterToAdd;
    
    emitterToAdd.setEmitType(EMIT_LINE);
    emitterToAdd.setLine(_p1, _p2);
    m_aEmitters[_name] = emitterToAdd;
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
