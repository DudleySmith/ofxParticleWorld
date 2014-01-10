#pragma once

#include "ofMain.h"
#include "ofxParticle.h"
#include "ofxAttractor.h"
#include "ofxEmitter.h"
#include "ofxColorSet.h"



class ofxParticleWorld{

public:
    void setup(ofxColorSet &_colorSet);
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
    
    vector <ofxParticle>    m_aParts;
    vector <ofxAttractor>   m_aAttractors;
    vector <ofxEmitter>     m_aEmitters;
    
    ofxColorSet             *m_pColorSet;
    
public:
    ofParameterGroup     m_pgSets;
    
private:
    ofParameter<int>      m_pxRenderMode;
    ofParameter<int>      m_pxAttractMode;
    
    ofParameter<float>   m_pxSize;
    ofParameter<float>   m_pxRateSize;
    
    ofParameter<float>   m_pxCoefForces;
    ofParameter<float>   m_pxCoefForcesMin;
    ofParameter<float>   m_pxCoefForces_X;
    ofParameter<float>   m_pxCoefForces_Y;
    ofParameter<float>   m_pxPulse;
    ofParameter<float>   m_pxDrag;
    ofParameter<float>   m_pxDistMin;
    ofParameter<float>   m_pxDistMax;
    ofParameter<float>   m_pxVelMax;
    
    ofParameter<float>   m_pxLifeBase;
    ofParameter<bool>    m_pxEternalLife;
		
};
