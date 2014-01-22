#pragma once

#include "ofxColorSet.h"

#include "ofxParticleWorldDefine.h"
#include "ofxAttractor.h"
#include "ofxParticle.h"

class ofxParticle;
class ofxAttractor;

class ofxParticleWorld{

public:
    void setup(ofxColorSet &_colorSet);
    void loadSettings();
    void setAttractors(vector<ofxAttractor> *attract);
    void update();
    void draw();
    void clear();
    
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
    
    vector<ofxParticle>     m_aParts;
    vector<ofxAttractor>    *m_pAttractors;
    
    ofxColorSet             *m_pColorSet;
public:
    vector<ofxParticle>     getTrackers();
    
    
public:
    ofParameterGroup     m_pgSets;
    
private:
    ofParameter<bool>    m_btPartsOn;

    ofParameterGroup     m_pgWorld;
    ofParameter<int>     m_pxRenderMode;
    ofParameter<int>     m_pxAttractMode;
    ofParameter<int>     m_pxColorMode;
    ofParameter<float>   m_pxVelMax;
    ofParameter<int>     m_pxNbPartsMax;
    ofParameter<int>     m_pxFpsSaveMin;
    ofParameter<int>     m_pxFpsSaveMax;
    ofParameter<float>   m_pxZMax;
    
    ofParameterGroup     m_pgParts;
    ofParameter<float>   m_pxSize;
    ofParameter<float>   m_pxRateSize;
    ofParameter<float>   m_pxLifeBase; // Special access
    ofParameter<float>   m_pxLifeReal;
    ofParameter<bool>    m_pxEternalLife;
    
    ofParameterGroup     m_pgAttractions;
    ofParameter<float>   m_pxCoefForces;
    ofParameter<float>   m_pxCoefForcesMin;
    ofParameter<float>   m_pxCoefForces_X;
    ofParameter<float>   m_pxCoefForces_Y;
    ofParameter<float>   m_pxDrag;
    ofParameter<float>   m_pxDistMin;
    ofParameter<float>   m_pxDistMax;
    ofParameter<int>     m_pxMaxProxCounter;
    
    ofParameterGroup     m_pgEmissions;
    ofParameter<float>   m_pxPulse;
    ofParameter<float>   m_pxFlowBase;
    ofParameter<float>   m_pxFlowReal;
    
public:
    partRenderMode getPxRenderMode(){return m_pxRenderMode.cast<partRenderMode>();}
    partAttractorMode getPxAttractMode(){return m_pxAttractMode.cast<partAttractorMode>();}
    partColorMode getPxColorMode(){return m_pxColorMode.cast<partColorMode>();}
    float getPxVelMax(){return m_pxVelMax.get();}
    int getPxPartsMax(){return m_pxNbPartsMax.get();}
    float getPxFpsSaveMin(){return m_pxFpsSaveMin.get();}
    float getPxFpsSaveMax(){return m_pxFpsSaveMax.get();}
    float getPxZMax(){return m_pxZMax.get();}
    
    float getPxSize(){return m_pxSize.get();}
    float getPxRateSize(){return m_pxRateSize.get();}
    //float getPxLifeBase(){return m_pxLifeBase.get();}
    bool  getPxEternalLife(){return m_pxEternalLife.get();}
    
    float getPxCoefForces(){return m_pxCoefForces.get();}
    float getPxForcesMin(){return m_pxCoefForcesMin.get();}
    float getPxForcesX(){return m_pxCoefForces_X.get();}
    float getPxForcesY(){return m_pxCoefForces_Y.get();}
    float getPxDrag(){return m_pxDrag.get();}
    float getPxDistMin(){return m_pxDistMin.get();}
    float getPxDistMax(){return m_pxDistMax.get();}
    float getPxMaxProxCounter(){return m_pxMaxProxCounter.get();}
    
    float getPxPulse(){return m_pxPulse.get();}
//    float getPxFlowBase(){return m_pxFlowBase.get();}
//    float getPxFlowReal(){return m_pxFlowReal.get();}
    
    // Special acces to life because of FPS saving
private:
    float getFpsSaveRate();
public:
    float getLife();
    float getFlow();
};
