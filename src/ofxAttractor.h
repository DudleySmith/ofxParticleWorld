//
//  ofxAttractor.h
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 06/01/2014.
//
//

#pragma once

#include "ofxParticleWorldDefine.h"
#include "ofxParticleWorld.h"
#include "ofxConstraint.h"

class ofxParticleWorld;
class ofxConstraint;

class ofxAttractor : public ofxConstraint{

public:
    virtual ~ofxAttractor();
    ofxAttractor();
    ofxAttractor(ofxParticleWorld &_pWorld);
    ofxAttractor(ofxParticleWorld &_pWorld, ofPoint _p1);
    ofxAttractor(ofxParticleWorld &_pWorld, ofPoint _p1, ofPoint _p2);
    
    ofxAttractor(ofxAttractor const &_a);

    
private:
    int m_iProxCounter;
    
public:
    void draw();
    
    void incProximityCounter();
    void resetProximityCounter();
    float getProximityRate();
    
};
