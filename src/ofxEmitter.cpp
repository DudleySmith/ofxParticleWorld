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
void ofxEmitter::draw()
{
    ofNoFill();
    ofCircle(m_oPt1, 10);
    ofFill();
    ofCircle(m_oPt1, 4);
   
    ofNoFill();
    ofCircle(m_oPt2, 10);
    ofFill();
    ofCircle(m_oPt2, 4);
    
    ofLine(m_oPt1, m_oPt2);
    
}

// -----------------------------------------------------------------------
void ofxEmitter::setPoint(ofPoint _P1){
    m_oPt1 = _P1;
    m_oPt2 = _P1;
}

// -----------------------------------------------------------------------
void ofxEmitter::setLine(ofPoint _P1, ofPoint _P2){
    m_oPt1 = _P1;
    m_oPt2 = _P2;
}
