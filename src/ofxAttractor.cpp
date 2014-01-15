//
//  ofxAttractor.cpp
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 06/01/2014.
//
//

#include "ofxAttractor.h"

// -----------------------------------------------------------------------
ofxAttractor::~ofxAttractor(){
    m_pWorld = NULL;
}

// -----------------------------------------------------------------------
ofxAttractor::ofxAttractor():ofxConstraint(){
    
}

// -----------------------------------------------------------------------
ofxAttractor::ofxAttractor(ofxParticleWorld &_pWorld):ofxConstraint(_pWorld){
    
}

// -----------------------------------------------------------------------
ofxAttractor::ofxAttractor(ofxParticleWorld &_pWorld, ofPoint _p1):ofxConstraint(_pWorld, _p1){
    
}

// -----------------------------------------------------------------------
ofxAttractor::ofxAttractor(ofxParticleWorld &_pWorld, ofPoint _p1, ofPoint _p2):ofxConstraint(_pWorld, _p1, _p2){
    
}

// -----------------------------------------------------------------------
ofxAttractor::ofxAttractor(ofxAttractor const &_a){
    // -
    m_oPt1 = _a.m_oPt1;
    m_oPt2 = _a.m_oPt2;
    m_eType = _a.m_eType;
    
    m_pWorld = _a.m_pWorld;
    
}

// -----------------------------------------------------------------------
void ofxAttractor::draw()
{
    
    ofPushStyle();
    ofSetColor(200,0,0);
    ofxConstraint::draw();
    ofPopStyle();
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(0.5*(m_oPt1.x+m_oPt2.x) + 10, 0.5*(m_oPt1.y+m_oPt2.y) + 10);
    
    ofSetColor(200*getProximityRate());
    
    ofRect(0, 0, 10, 10);
    ofDrawBitmapString(ofToString(getProximityRate()), ofPoint(0,30));
    ofDrawBitmapString(ofToString(m_iProxCounter), ofPoint(0,40));
    
    resetProximityCounter();
    
    ofPopMatrix();
    ofPopStyle();
    
}

// -----------------------------------------------------------------------
void ofxAttractor::incProximityCounter(){
    m_iProxCounter++;
}

// -----------------------------------------------------------------------
void ofxAttractor::resetProximityCounter(){
    m_iProxCounter=0;
}

// -----------------------------------------------------------------------
float ofxAttractor::getProximityRate(){
    return ((float)m_iProxCounter /  (float)m_pWorld->getPxMaxProxCounter());
}

