//
//  ofxAttractor.h
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 06/01/2014.
//
//

#pragma once

#include <iostream>

class ofxAttractor {
    
public:
    ofxAttractor();
    
    // Position --
private:
    ofPoint m_oPos;
public:
    void setPos(ofPoint _pos){m_oPos = _pos;}
    ofPoint getPos(){return m_oPos;}
    
};
