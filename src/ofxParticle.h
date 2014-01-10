#pragma once
#include "ofMain.h"

#include "ofxAttractor.h"
#include "ofxParticleWorldDefine.h"

class ofxParticle{

public:
    ofxParticle();
		
    void setAttractPoints( vector <ofxAttractor> * attract );
    void setColor(ofColor _color){m_oColor = _color;};
		
    void reset(ofVec3f _originVel);
    void update(ofParameterGroup _settings);
    void draw();
		
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    
    float drag;
    float uniqueVal;
    float scale;
		
    partAttractorMode    m_eAttractMode;
    partRenderMode       m_eRenderMode;
	
    vector <ofxAttractor> * attractPoints;
    
    ofColor m_oColor;
    
};