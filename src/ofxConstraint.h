//
//  ofxConstraint.h
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 12/01/2014.
//
//

#pragma once

#include "ofMain.h"

enum constraintType{
    CONSTRAINT_RANDOM = 0,
    CONSTRAINT_POINT,
    CONSTRAINT_LINE,
    CONSTRAINT_SQUARE
};

class ofxConstraint {
    
public:
    ofxConstraint();
    virtual ~ofxConstraint();
    
    void draw();
    
    // Position --
protected:
    ofPoint m_oPt1;
    ofPoint m_oPt2;

    constraintType m_eType;
    
public:
    void setPoint(ofPoint _pt1);
    void setLine(ofPoint _pt1, ofPoint _pt2);
    
    ofPoint getPt1(){return m_oPt1;}
    ofPoint getPt2(){return m_oPt2;}
    ofVec3f getLine(){return m_oPt2 - m_oPt1;}
    
    void setType(constraintType _type){m_eType = _type;}
    constraintType getType(){return m_eType;}
    
    ofVec3f shortDistance(ofVec3f _pt);
    
};
