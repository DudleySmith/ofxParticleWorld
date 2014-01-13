#pragma once
#include "ofMain.h"

#include "ofxParticleWorldDefine.h"
#include "ofxParticleWorld.h"
#include "ofxAttractor.h"

class ofxParticleWorld;
class ofxAttractor;

class ofxParticle{

public:
    ofxParticle();
    ofxParticle(ofxParticle const &_p);
    ofxParticle(ofxParticleWorld     &m_pWorld);
    virtual ~ofxParticle();
    
private:
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    
    float drag;
    float m_fUniqueVal;
    float scale;
    
    float m_fLifeTimeInSec;
    float m_fStartTime;
    
    long   m_iNumber;
		
    partAttractorMode    m_eAttractMode;
    partRenderMode       m_eRenderMode;
    partColorMode        m_eColorMode;
	
    vector<ofxAttractor> *m_pAttractPoints;
    ofxParticleWorld     *m_pWorld;
    
    ofColor m_oColor;
    
public:
    void setAttractPoints( vector <ofxAttractor> * attract );
    void setColor(ofColor _color){m_oColor = _color;};
    void setPos(ofPoint _pos){pos = _pos;};
    
    float getLifeTime(){return m_fLifeTimeInSec;}
    
    void reset(ofVec3f _originVel);
    void update();
    void draw();
    
    bool isDead(float _lifeInSec);
    
    ofColor colorToDraw();
    
    
};