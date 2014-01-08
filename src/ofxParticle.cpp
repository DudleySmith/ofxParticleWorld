#include "ofxParticle.h"

//------------------------------------------------------------------
ofxParticle::ofxParticle(){
	attractPoints = NULL;
}

//------------------------------------------------------------------
void ofxParticle::setMode(partAttractorMode newMode){
	mode = newMode;
}

//------------------------------------------------------------------
void ofxParticle::setAttractPoints( vector <ofxAttractor> * attract ){
	attractPoints = attract;
}

//------------------------------------------------------------------
void ofxParticle::reset(ofVec3f _originVel){
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);
	
	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();
	/*
	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);
	*/
    vel = _originVel;
    
	frc   = ofPoint(0,0,0);
	
	scale = ofRandom(0.5, 1.0);
	
	if( mode == PARTICLE_ATTRACTOR_MODE_NOISE ){
		drag  = ofRandom(0.97, 0.99);
		vel.y = fabs(vel.y) * 3.0; //make the particles all be going down
	}else{
		drag  = ofRandom(0.95, 0.998);	
	}
    
    m_oColor.setHsb(ofRandom(0, 255), ofRandom(100, 255), 255);
    
}

//------------------------------------------------------------------
void ofxParticle::update(ofParameterGroup _settings){
    
    // 0 - Set the settings
    scale = _settings.get(cpxSize).cast<float>() * _settings.get(cpxRateSize).cast<float>();

    float forceCoef = _settings.get(cpxCoefForces).cast<float>();
    float forceCoefMin = _settings.get(cpxCoefForcesMin).cast<float>();
    
    float localDrag = drag*_settings.get(cpxDrag).cast<float>();
    

	//1 - APPLY THE FORCES BASED ON WHICH MODE WE ARE IN
    if( mode == PARTICLE_ATTRACTOR_MODE_NOISE){
		//lets simulate falling snow 
		//the fake wind is meant to add a shift to the particles based on where in x they are
		//we add pos.y as an arg so to prevent obvious vertical banding around x values - try removing the pos.y * 0.006 to see the banding
		float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.006, ofGetElapsedTimef() * 0.6);
		
		frc.x = fakeWindX * 0.25 + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
		frc.y = ofSignedNoise(uniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;

		vel *= localDrag; 
		vel += frc * forceCoef;
		
		//we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
		if( pos.y + vel.y > ofGetHeight() ){
			pos.y -= ofGetHeight();
		}
	}
	else if( mode == PARTICLE_ATTRACTOR_MODE_ATTRACT){
		
		if( attractPoints ){

			//1 - find closest attractPoint 
			ofxAttractor closestAttractor;
			int closest = -1; 
			float closestDist = 9999999;
			
			for(unsigned int i = 0; i < attractPoints->size(); i++){
				float lenSq = ( attractPoints->at(i).getPos()-pos ).lengthSquared();
				if( lenSq < closestDist ){
					closestDist = lenSq;
					closest = i;
				}
			}
			
			//2 - if we have a closest point - lets calcuate the force towards it
			if( closest != -1 ){
				closestAttractor = attractPoints->at(closest);
				float dist = sqrt(closestDist);
				
				//in this case we don't normalize as we want to have the force proportional to distance 
				frc = closestAttractor.getPos() - pos;
                
                vel *= localDrag;
				 
				//lets also limit our attraction to a certain distance
				if( dist < _settings.get(cpxDistMax).cast<float>() && dist > _settings.get(cpxDistMin).cast<float>()){
					vel += frc * forceCoefMin;
				}else{
					//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy. 			
					frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
					frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
                    
                    vel += frc * forceCoef;
				}
				
			}
		
		}
		
	}
	else if( mode == PARTICLE_ATTRACTOR_MODE_REPEL){
		
		if( attractPoints ){

			//1 - find closest attractPoint
			ofxAttractor closestAttractor;
			int closest = -1;
			float closestDist = 9999999;
            
			for(unsigned int i = 0; i < attractPoints->size(); i++){
				float lenSq = ( attractPoints->at(i).getPos()-pos ).lengthSquared();
				if( lenSq < closestDist ){
					closestDist = lenSq;
					closest = i;
				}
			}
            
			//2 - if we have a closest point - lets calcuate the force towards it
			if( closest != -1 ){
				closestAttractor = attractPoints->at(closest);
				float dist = sqrt(closestDist);
				
                frc = closestAttractor.getPos()-pos;
                frc.normalize();
                
                //let get the distance and only repel points close to the mouse
                vel *= localDrag;
                
                if( dist < _settings.get(cpxDistMax).cast<float>()){
                    vel += -frc * forceCoef; //notice the frc is negative
                }else{
                    //if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
					frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
					frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
                    
                    vel += frc * forceCoefMin;
                }

			}
            
            
		}
		
	}

	
	//2 - UPDATE OUR POSITION
	vel.x *= _settings.get(cpxCoefForces_X).cast<float>();
    vel.y *= _settings.get(cpxCoefForces_Y).cast<float>();
    vel.limit(_settings.get(cpxVelMax).cast<float>());
    
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
		
}

//------------------------------------------------------------------
void ofxParticle::draw(){

	ofSetColor(m_oColor);
    
	ofCircle(pos.x, pos.y, scale * 4.0);
    
}

