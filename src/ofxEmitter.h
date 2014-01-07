//
//  ofxEmitter.h
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 06/01/2014.
//
//

#pragma once

#include <iostream>
#include "ofMain.h"

enum emitterMode{
	EMITTER_MODE_RANDOM = 0,
	EMITTER_MODE_POINT,
	EMITTER_MODE_LINE
};


class ofxEmitter {

public:
    ofxEmitter();
    
    // Position --
private:
    ofPoint m_oPos;
public:
    void setPos(ofPoint _pos){m_oPos = _pos;}
    ofPoint getPos(){return m_oPos;}
    
};
