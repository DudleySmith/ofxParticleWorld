//
//  ofxEmitter.h
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 10/01/2014.
//
//

#pragma once

#include "ofxParticleWorldDefine.h"
#include "ofxConstraint.h"
#include "ofxParticle.h"

class ofxConstraint;

class ofxEmitter : public ofxConstraint{
    
public:
    virtual ~ofxEmitter();
    ofxEmitter();
    ofxEmitter(ofxParticleWorld &m_pWorld);
    ofxEmitter(ofxParticleWorld &m_pWorld, ofPoint _p1);
    ofxEmitter(ofxParticleWorld &m_pWorld, ofPoint _p1, ofPoint _p2);
    
    ofxEmitter(ofxEmitter const &_e);
    
private:
    ofVec3f m_oPulse;
    
    float   m_fFlow;
    bool    m_bEmit;
    float   m_fLastTimeEmit; // In seconds
    
public:
    void draw();
    void update();
    
    void setFlow(float _flow){m_fFlow = _flow;}
    
    float getProximityRate();
    
};
