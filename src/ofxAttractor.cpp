//
//  ofxAttractor.cpp
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 06/01/2014.
//
//

#include "ofxAttractor.h"

// -----------------------------------------------------------------------
void ofxAttractor::draw()
{
    ofPushStyle();
    ofSetColor(ofColor(200,0,0));
    
    ofxConstraint::draw();
    ofPopStyle();

}


