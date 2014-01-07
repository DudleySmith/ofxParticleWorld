#pragma once

#include "ofMain.h"
#include "ofxParticle.h"
#include "ofxAttractor.h"
#include "ofxEmitter.h"

class ofxParticleWorld{

	public:
		void setup();
        void loadSettings();
		void update();
        void drawParticles();
        void drawAttractors();
        void drawEmitters();
        void resetParticles();
    
        void addAttractPoints(string _name, ofPoint _pos);
    
        /*
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		*/
    
		partAttractorMode    currentMode;
		
		vector <ofxParticle> p;
    
    vector <ofxAttractor>   m_aAttractors;
    vector <ofxEmitter>     m_aEmitters;
    //vector <ofxAttractor> attractPointsWithMovement;
    
public:
    ofParameterGroup     m_pgPartsSettings;
private:
    ofParameter<float>   m_pxSize;
    ofParameter<float>   m_pxCoefForces;
    ofParameter<float>   m_pxCoefForces_X;
    ofParameter<float>   m_pxCoefForces_Y;
    ofParameter<float>   m_pxPulse;
    ofParameter<float>   m_pxLifeBase;
    ofParameter<float>   m_pxFriction;
    ofParameter<bool>    m_pxEternalLife;
		
};
