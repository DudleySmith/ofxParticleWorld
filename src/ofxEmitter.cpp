//
//  ofxEmitter.cpp
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 10/01/2014.
//
//

#include "ofxEmitter.h"

// -----------------------------------------------------------------------
ofxEmitter::ofxEmitter(){
}

// -----------------------------------------------------------------------
ofxEmitter::ofxEmitter(ofxParticleWorld &_world) : ofxConstraint(_world){
    m_fLastTimeEmit = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
ofxEmitter::~ofxEmitter(){
    m_pWorld = NULL;
}

//--------------------------------------------------------------
ofxEmitter::ofxEmitter(ofxParticleWorld &_world, ofPoint _p1) : ofxConstraint(_world, _p1){
    m_fLastTimeEmit = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
ofxEmitter::ofxEmitter(ofxParticleWorld &_world, ofPoint _p1, ofPoint _p2) : ofxConstraint(_world, _p1, _p2){
    m_fLastTimeEmit = ofGetElapsedTimeMillis();
}

// -----------------------------------------------------------------------
void ofxEmitter::draw()
{
    ofPushStyle();
    ofSetColor(ofColor(0,0,200));
    
    ofxConstraint::draw();
    ofPopStyle();
}

// -----------------------------------------------------------------------
ofxEmitter::ofxEmitter(ofxEmitter const &_e){
    // -
    m_oPt1 = _e.m_oPt1;
    m_oPt2 = _e.m_oPt2;
    m_eType = _e.m_eType;
    
    m_pWorld = _e.m_pWorld;
    
}

// -----------------------------------------------------------------------
void ofxEmitter::update(){
    
    ofxParticle partToEmit(*m_pWorld);
    m_fFlow = m_pWorld->getFlow();
    m_bEmit = true;
    
    // First calculate how many parts to emit, depends on the flow
    float dt = ofGetElapsedTimeMillis()/1000.0f - m_fLastTimeEmit;
    
    m_fLastTimeEmit = ofGetElapsedTimeMillis()/1000.0f;

    int   nbParts = dt * m_fFlow;
    
    if (m_bEmit==true && nbParts>0) {
        
        // Preparing the part
        ofVec3f originVel;
        ofVec3f originPos;
        ofVec3f direction = m_oPt2 - m_oPt1;
        
        float pulse = m_pWorld->getPxPulse();
        
        
        // Generic velocity start : Random
        originVel.set(ofRandom(-1*pulse, pulse), ofRandom(-1*pulse, pulse), ofRandom(-1*pulse, pulse));
        // Overriden when EMIT_LINE with some calculation with direction
        
        
        for (int nbToEmit = 0; nbToEmit<nbParts; nbToEmit++) {
            
            switch (m_eType) {
                case CONSTRAINT_RANDOM:
                    originPos.set(ofRandomWidth(), ofRandomHeight(), 0);
                    break;
                    
                case CONSTRAINT_POINT:
                    originPos = m_oPt1;
                    break;
                    
                case CONSTRAINT_LINE:
                    originPos = m_oPt1 + ofRandom(0, 1)*direction;
                    //originPos = 0.5*(m_oPt1 + m_oPt2);
                    
                    originVel.getCrossed(direction);
                    originVel.scale(ofRandom(0, pulse));
                    break;
                    
                case CONSTRAINT_SQUARE:
                    originPos.set(ofRandom(m_oPt1.x, m_oPt2.x), ofRandom(m_oPt1.y, m_oPt2.y), ofRandom(m_oPt1.z, m_oPt2.z));
                    break;
                    
                default:
                    break;
            }
            
            partToEmit.reset(originVel);
            partToEmit.setPos(originPos);
            
            m_pWorld->m_aParts.push_back(partToEmit);
            
        }
        
    }
}

// -----------------------------------------------------------------------
float ofxEmitter::getProximityRate(){
    float ttttt = m_pWorld->m_aParts.size();
    return ttttt;
}