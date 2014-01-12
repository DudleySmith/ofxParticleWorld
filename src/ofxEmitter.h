//
//  ofxEmitter.h
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 10/01/2014.
//
//

#pragma once

#include "ofMain.h"
#include "ofxParticle.h"
#include "ofxConstraint.h"

class ofxParticleWorld;

class ofxEmitter : public ofxConstraint{
    
public:
    virtual ~ofxEmitter();
    ofxEmitter();
    ofxEmitter(ofxEmitter const &_e);
    ofxEmitter(ofxParticleWorld &m_pWorld);
    ofxEmitter(ofxParticleWorld &m_pWorld, ofPoint _p1);
    ofxEmitter(ofxParticleWorld &m_pWorld, ofPoint _p1, ofPoint _p2);
        
private:
    ofVec3f m_oPulse;
    
    ofxParticleWorld *m_pWorld;
    
    float   m_fFlow;
    bool    m_bEmit;
    float   m_fLastTimeEmit; // In seconds
    
public:
    void draw();
    void update();
    
    void setFlow(float _flow){m_fFlow = _flow;}
    
};
