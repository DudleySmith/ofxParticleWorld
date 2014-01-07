#pragma once
#include "ofMain.h"

#include "ofxAttractor.h"

enum partAttractorMode{
	PARTICLE_ATTRACTOR_MODE_ATTRACT = 0,
	PARTICLE_ATTRACTOR_MODE_REPEL,
	PARTICLE_ATTRACTOR_MODE_NOISE
};

class ofxParticle{

	public:
		ofxParticle();
		
		void setMode(partAttractorMode newMode);
		void setAttractPoints( vector <ofxAttractor> * attract );

		void reset();
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