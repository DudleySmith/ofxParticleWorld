#include "ofxParticle.h"

//------------------------------------------------------------------
ofxParticle::ofxParticle(){
	m_pAttractPoints = NULL;
    m_pWorld = NULL;
}

ofxParticle::ofxParticle(ofxParticle const &_p){
    m_pWorld = _p.m_pWorld;
    m_pAttractPoints = _p.m_pAttractPoints;
    
    pos = _p.pos;
    frc = _p.frc;
    
    m_eAttractMode = _p.m_eAttractMode;
    m_eRenderMode = _p.m_eRenderMode;
    m_eColorMode = _p.m_eColorMode;
    
    m_iNumber = _p.m_iNumber;
    
    reset(_p.vel);
    
}


//------------------------------------------------------------------
ofxParticle::ofxParticle(ofxParticleWorld &_world){
    m_pWorld = &_world;
    m_iNumber = _world.m_aParts.size();
	m_pAttractPoints = NULL;
}

//------------------------------------------------------------------
ofxParticle::~ofxParticle(){
	m_pAttractPoints = NULL;
}

//------------------------------------------------------------------
void ofxParticle::setAttractPoints( vector <ofxAttractor> * attract ){
	m_pAttractPoints = attract;
}

//------------------------------------------------------------------
void ofxParticle::reset(ofVec3f _originVel){
	//the unique val allows us to set properties slightly differently for each particle
	m_fUniqueVal = ofRandom(-10000, 10000);
	
	//pos.x = ofRandomWidth();
	//pos.y = ofRandomHeight();
	/*
	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);
	*/
    vel = _originVel;
    
	frc   = ofPoint(0,0,0);
	
	scale = ofRandom(0.5, 1.0);
	
	if( m_eAttractMode == PATTRACTOR_NOISE ){
		drag  = ofRandom(0.97, 0.99);
		vel.y = fabs(vel.y) * 3.0; //make the particles all be going down
	}else{
		drag  = ofRandom(0.95, 0.998);	
	}
    
    m_fLifeTimeInSec    = 0;
    m_fStartTime        = ofGetElapsedTimeMillis();
    
}

//------------------------------------------------------------------
void ofxParticle::update(){
    
    // Calcul du temps de vie en secondes
    m_fLifeTimeInSec = (ofGetElapsedTimeMillis() - m_fStartTime) / 1000;
    
    // 0 - Set the settings
    scale = m_pWorld->getPxSize() * m_pWorld->getPxRateSize();

    float forceCoef = m_pWorld->getPxCoefForces();
    float forceCoefMin = m_pWorld->getPxForcesMin();
    
    float localDrag = drag*m_pWorld->getPxDrag();
    
    m_eAttractMode = m_pWorld->getPxAttractMode();
    m_eRenderMode = m_pWorld->getPxRenderMode();
    m_eColorMode = m_pWorld->getPxColorMode();
    m_oColor = colorToDraw();
    
	//1 - APPLY THE FORCES BASED ON WHICH MODE WE ARE IN
    if( m_eAttractMode == PATTRACTOR_NOISE){
		//lets simulate falling snow 
		//the fake wind is meant to add a shift to the particles based on where in x they are
		//we add pos.y as an arg so to prevent obvious vertical banding around x values - try removing the pos.y * 0.006 to see the banding
		float fakeWindX = ofSignedNoise(pos.x * forceCoefMin, pos.y * forceCoefMin, ofGetElapsedTimef() * forceCoef);
		float fakeWindY = ofSignedNoise(pos.y * forceCoefMin, pos.y * forceCoefMin, ofGetElapsedTimef() * forceCoef);
		float fakeWindZ = ofSignedNoise(pos.z * forceCoefMin, pos.z * forceCoefMin, ofGetElapsedTimef() * forceCoef);
		
		frc.x = fakeWindX * 0.25 + ofSignedNoise(m_fUniqueVal, pos.x * 0.04) * 0.6;
        frc.y = fakeWindY * 0.25 + ofSignedNoise(m_fUniqueVal, pos.y * 0.04) * 0.6;
        frc.z = fakeWindZ * 0.25 + ofSignedNoise(m_fUniqueVal, pos.z * 0.04) * 0.6;
        
		//frc.y = ofSignedNoise(m_fUniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;

		vel *= localDrag; 
		vel += frc * forceCoef;
		
		// we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
        
        /*
		if( pos.y + vel.y > ofGetHeight() ){
			pos.y -= ofGetHeight();
		}
        */
        
	}else if( m_eAttractMode == PATTRACTOR_ATTRACT || m_eAttractMode == PATTRACTOR_REPEL){
		if( m_pAttractPoints ){

			// 1 - find closest attractPoint
			ofxAttractor                    *closestAttractor;
            vector<ofxAttractor>::iterator  oneAttractor;
            
			bool findClosest = false;
			float closestDist = 9999999;
			
            for(oneAttractor = m_pAttractPoints->begin(); oneAttractor!=m_pAttractPoints->end(); oneAttractor++){
                
                float lenSq;
                
                if((*oneAttractor).getType()==CONSTRAINT_POINT){
                    lenSq = (oneAttractor->getPt1() - pos).lengthSquared();
                }else if ((*oneAttractor).getType()==CONSTRAINT_LINE){
                    lenSq = oneAttractor->shortDistance(pos, true).lengthSquared();
                }
                
                if( lenSq < closestDist && lenSq < (m_pWorld->getPxDistMax()*m_pWorld->getPxDistMax())){
					closestDist = lenSq;
                    closestAttractor = &(*oneAttractor);
                    findClosest = true;
				}
			}
			
			// 2 - if we have a closest point - lets calcuate the force towards it
			if( findClosest == true){
                
                float dist = sqrt(closestDist);
				
				if(closestAttractor->getType()==CONSTRAINT_POINT){
                    frc = closestAttractor->getPt1() - pos;
                }else if (closestAttractor->getType()==CONSTRAINT_LINE){
                    frc = closestAttractor->shortDistance(pos, true);
                }
                
                if (m_eAttractMode == PATTRACTOR_ATTRACT) {
                    
                    vel *= localDrag;
                    
                    // Count is only about max proximity
                    if(dist < m_pWorld->getPxDistMax()){
                        closestAttractor->incProximityCounter();
                    }
                    
                    //lets also limit our attraction to a certain distance
                    if(dist < m_pWorld->getPxDistMax() && dist > m_pWorld->getPxDistMin()){
                        vel += frc * forceCoefMin;
                        
                    }else{
                        //if the particles are not close to us, lets add a little bit of random movement using noise. this is where m_fUniqueVal comes in handy.
                         frc.x = ofSignedNoise(m_fUniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
                         frc.y = ofSignedNoise(m_fUniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
                         frc.z = ofSignedNoise(m_fUniqueVal, pos.z * 0.01, ofGetElapsedTimef()*0.2);
                         
                         vel += frc * forceCoef;

                    }
                    
                    
                } else if(m_eAttractMode == PATTRACTOR_REPEL){
                    
                    frc.normalize();
                    vel *= localDrag;
                    
                    if(dist<m_pWorld->getPxDistMax()){
                        vel += -frc * forceCoef; //notice the frc is negative
                    }else{
                        //if the particles are not close to us, lets add a little bit of random movement using noise. this is where m_fUniqueVal comes in handy.
                        frc.x = ofSignedNoise(m_fUniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
                        frc.y = ofSignedNoise(m_fUniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
                        frc.z = ofSignedNoise(m_fUniqueVal, pos.z * 0.01, ofGetElapsedTimef()*0.2);
                        
                        vel += frc * forceCoefMin;
                    }
                }

				
			}
		
		}
	}
	
	//2 - UPDATE OUR POSITION
	vel.x *= m_pWorld->getPxForcesX();
    vel.y *= m_pWorld->getPxForcesY();
    vel.limit(m_pWorld->getPxVelMax());
    
	pos += vel; 
	
	
	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN 
	//we could also pass in bounds to check - or alternatively do this at the ofApp level
	if( pos.x > ofGetWidth() ){
		pos.x = ofGetWidth();
		vel.x *= -1.0;
	}else if( pos.x < 0 ){
		pos.x = 0;
		vel.x *= -1.0;
	}
	if( pos.y > ofGetHeight() ){
		pos.y = ofGetHeight();
		vel.y *= -1.0;
	}
	else if( pos.y < 0 ){
		pos.y = 0;
		vel.y *= -1.0;
	}	
    if( pos.z > m_pWorld->getPxZMax() ){
		pos.z = m_pWorld->getPxZMax();
		vel.z *= -1.0;
	}
	else if( pos.z < -1.0*m_pWorld->getPxZMax()){
		pos.z = -1.0*m_pWorld->getPxZMax();
		vel.z *= -1.0;
	}
	
}

//------------------------------------------------------------------
void ofxParticle::draw(){

	//
    // -------------------------------------------------------------------------------------
    // RENDU DES PARTICULES --------------------------------------------------------------
    // -------------------------------------------------------------------------------------
    //
    
    // STYLE --------------------------
    ofPushStyle();
    ofSetLineWidth(1);
    ofEnableAlphaBlending();
    // LOCATION ----------------------
    ofPushMatrix();
    ofTranslate(pos);
    ofScale(scale, scale, scale);
    
    ofSetColor(m_oColor);
    
    switch (m_eRenderMode)
    {
            // CARRE PLEIN ---------------------------------------------------------------------
        case PRENDER_QUAD:
            ofFill();
            ofRect(- 0.5, - 0.5, 1, 1);
            break;
            // CARRE Vide ---------------------------------------------------------------------
        case PRENDER_SQUARE:
            ofNoFill();
            ofRect(- 0.5, - 0.5, 1, 1);
            break;
            // Rond Plein ---------------------------------------------------------------------
        case PRENDER_DISC:
            ofFill();
            ofCircle(0, 0, 1);
            break;
            // Rond Vide ---------------------------------------------------------------------
        case PRENDER_CIRCLE:
            ofNoFill();
            ofCircle(0, 0, 1);
            break;
            // 3 Ronds vides ----------------------------------------------------------------------
        case PRENDER_3RONDS:
            ofNoFill();
            ofCircle(0, 0, 1/3);
            ofCircle(0, 0, 2/3);
            ofCircle(0, 0, 1);
            break;
            // Trait ----------------------------------------------------------------------
        case PRENDER_TRAIT:
            ofNoFill();
            ofLine(- 0.5, 0, + 0.5, 0);
            break;
            // Croix ----------------------------------------------------------------------
        case PRENDER_CROIX:
            ofNoFill();
            ofLine(- 0.5, 0, 0.5, 0);
            ofLine(0, - 0.5, 0, 0.5);
            break;
            // 3RONDS ----------------------------------------------------------------------
        case PRENDER_X:
            ofNoFill();
            ofRotate(90);
            ofLine(- 0.5, 0, 0.5, 0);
            ofLine(0, - 0.5, 0, 0.5);
            break;
            // HEXAGON -----------------------------------------------------------------------
        case PRENDER_HEXAGON:
            ofNoFill();
            ofSetCircleResolution(6);
            ofCircle(0, 0, 1);
            break;
            // PENTAGON -----------------------------------------------------------------------
        case PRENDER_PENTAGON:
            ofNoFill();
            ofSetCircleResolution(5);
            ofCircle(0, 0, 1);
            break;
            // OCTOGON -----------------------------------------------------------------------
        case PRENDER_OCTOGON:
            ofNoFill();
            ofSetCircleResolution(8);
            ofCircle(0, 0, 1);
            break;
            // OBLIQUES -----------------------------------------------------------------------
        case PRENDER_OBLIQU:
            ofNoFill();
            ofLine(0, 1, 1, 0);
            break;
            // LETTERS ----------------------------------------------------------------------
        case PRENDER_LETTRE:
            ofNoFill();
            ofDrawBitmapString(ofToString(char(ofRandom(0,255))),0,0);
            // Code de dessin
            break;
        default:
            break;
    }
    
    // STYLE --------------------------
    ofPopStyle();
    // LOCATION ----------------------
    ofPopMatrix();
    

//	ofCircle(pos.x, pos.y, scale * 4.0);
    
}

//------------------------------------------------------------------
bool ofxParticle::isDead(float _lifeInSec){

    if ((1000*m_fLifeTimeInSec + abs(m_fUniqueVal))>=1000*_lifeInSec) {
        return true;
    }else{
        return false;
    }
    
}

// -----------------------------------------------------------------
ofColor ofxParticle::colorToDraw(){
    
    float gradientProgress;
    ofColor colorToDraw;
    
    switch (m_eColorMode) {
        case PCOLOR_MODE_CREATION:
            gradientProgress = (float)m_iNumber / (float)m_pWorld->m_aParts.size();
            break;
            
        case PCOLOR_MODE_LIFE:
            if(isDead(m_pWorld->getLife())){
                gradientProgress = 1;
            }else{
                gradientProgress = m_fLifeTimeInSec / m_pWorld->getLife();
            }
            break;
            
        case PCOLOR_MODE_VEL:
            gradientProgress = vel.length() / m_pWorld->getPxVelMax();
            break;
            
        default:
            break;
    }
    
    colorToDraw = m_pWorld->m_pColorSet->getCurrentSetByProgress(gradientProgress);
    
    return colorToDraw;
    
}
