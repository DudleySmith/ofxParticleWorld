#pragma once
#include "ofMain.h"

#include "ofxAttractor.h"
#include "ofxParticleWorldDefine.h"

class ofxParticle{

	public:
		ofxParticle();
		
		void setMode(partAttractorMode newMode);
		void setAttractPoints( vector <ofxAttractor> * attract );

		void reset(ofVec3f _originVel);
		void update(ofParameterGroup _settings);
		void draw();		
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		
		partAttractorMode mode;
		
		vector <ofxAttractor> * attractPoints;
    
        ofColor m_oColor;
    
};