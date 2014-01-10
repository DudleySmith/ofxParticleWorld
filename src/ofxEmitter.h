//
//  ofxEmitter.h
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 10/01/2014.
//
//

#pragma once

#include "ofMain.h"
//#include "ofxParticleWorld.h"

class ofxParticleWorld;

enum emitType{
    EMIT_RANDOM = 0,
    EMIT_POINT,
    EMIT_LINE,
    EMIT_SQUARE
};

class ofxEmitter {
    
public:
    ofxEmitter();
    
private:
    ofPoint m_oPt1;
    ofPoint m_oPt2;
    
    ofVec3f m_oPulse;
    
    ofxParticleWorld *m_pWorld;
    emitType         m_eEmitType;
    
    float   m_rFlow;
    
public:
    void emit();
    void draw();
    void setFlow(float _flow){m_rFlow = _flow;}
    void setEmitType(emitType _emitType){m_eEmitType = _emitType;}
    
    void setPoint(ofPoint _P1);
    void setLine(ofPoint _P1, ofPoint _P2);
    
};
