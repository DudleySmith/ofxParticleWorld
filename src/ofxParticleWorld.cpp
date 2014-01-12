#include "ofApp.h"

//--------------------------------------------------------------
void ofxParticleWorld::setup(ofxColorSet& _colorSet){
    
    m_pColorSet = &_colorSet;
    
    loadSettings();
    
}

//--------------------------------------------------------------
void ofxParticleWorld::loadSettings(){

    
    // Settings ---------------
    m_pgSets.setName("Parts settings");
    
    m_pgWorld.setName("World");
    m_pgWorld.add(m_pxRenderMode.set("RenderMode", 0, PRENDER_NoRender, PRENDER_OBLIQU));
    m_pgWorld.add(m_pxAttractMode.set("AttractMode", 0, PATTRACTOR_ATTRACT, PATTRACTOR_NOISE));
    m_pgWorld.add(m_pxColorMode.set("ColorMode", 0, PCOLOR_MODE_CREATION, PCOLOR_MODE_VEL));
    m_pgWorld.add(m_pxVelMax.set("VelMax", 1, 0, 100));
    m_pgWorld.add(m_pxNbPartsMax.set("NbPartsMax", 1, 0, 100));
    m_pgWorld.add(m_pxFpsToSave.set("FpsMax", 1, 0, 60));
    m_pgWorld.add(m_pxZMax.set("ZMax", 1, 0, 100));
    
    m_pgParts.setName("Parts");
    m_pgParts.add(m_pxSize.set("Size", 0, 1, 20));
    m_pgParts.add(m_pxRateSize.set("RateSize", 0, 0, 1));
    m_pgParts.add(m_pxLifeBase.set("Life", 1, 0, 20));
    m_pgParts.add(m_pxEternalLife.set("IsEternalLife", 0));
    
    m_pgAttractions.setName("Attractions");
    m_pgAttractions.add(m_pxCoefForces.set("CoefForces", 0.4, 0, 2));
    m_pgAttractions.add(m_pxCoefForcesMin.set("CoefForcesMin", 0.05, 0, 0.1));
    m_pgAttractions.add(m_pxCoefForces_X.set("CoefForces_X", 0, 0, 1));
    m_pgAttractions.add(m_pxCoefForces_Y.set("CoefForces_Y", 0, 0, 1));
    m_pgAttractions.add(m_pxPulse.set("Pulse", 0.5, 0, 5));
    m_pgAttractions.add(m_pxDrag.set("Drag", 0.5, 0, 1));
    m_pgAttractions.add(m_pxDistMin.set("DistMin", 40, 0, 250));
    m_pgAttractions.add(m_pxDistMax.set("DistMax", 300, 0, 1000));
    
    m_pgEmissions.setName("Emissions");
    m_pgEmissions.add(m_pxPulse.set("Pulse", 0.5, 0, 1));
    m_pgEmissions.add(m_pxFlow.set("Flow", 40, 0, 200));

    m_pgSets.add(m_pgWorld);
    m_pgSets.add(m_pgParts);
    m_pgSets.add(m_pgAttractions);
    m_pgSets.add(m_pgEmissions);
    
}

//--------------------------------------------------------------
void ofxParticleWorld::update(){
    
    vector<ofxParticle>::iterator   oneParticle;
    
    for(oneParticle = m_aParts.begin(); oneParticle != m_aParts.end(); ++oneParticle){
        
        (*oneParticle).setAttractPoints(&m_aAttractors);
        
        if(getPxEternalLife()==false && (*oneParticle).isDead(getPxLifeBase()) == true){
            oneParticle = m_aParts.erase(oneParticle);
        }else{
            (*oneParticle).update();
        }
        
        if(oneParticle == m_aParts.end())   break;

    }
    
}

//--------------------------------------------------------------
void ofxParticleWorld::drawParticles(){
    
    vector<ofxParticle>::iterator   oneParticle;

    for(oneParticle = m_aParts.begin(); oneParticle != m_aParts.end(); oneParticle++){
        (*oneParticle).draw();
	}
}

//--------------------------------------------------------------
void ofxParticleWorld::drawAttractors(){
    
    for(unsigned int i = 0; i < m_aAttractors.size(); i++){
        m_aAttractors[i].draw();
    }
    
}


//--------------------------------------------------------------
void ofxParticleWorld::addAttractPoints(string _name, ofPoint _p1){
    
    ofxAttractor attractorToAdd;
    attractorToAdd.setPoint(_p1);
    attractorToAdd.setType(CONSTRAINT_POINT);
    
    m_aAttractors.push_back(attractorToAdd);
    
}

//--------------------------------------------------------------
void ofxParticleWorld::addAttractLine(string _name, ofPoint _p1, ofPoint _p2){
    
    ofxAttractor attractorToAdd;
    attractorToAdd.setLine(_p1, _p2);
    attractorToAdd.setType(CONSTRAINT_LINE);
    
    m_aAttractors.push_back(attractorToAdd);
    
}

//--------------------------------------------------------------
void ofxParticleWorld::clear(){
    m_aParts.erase(m_aParts.begin(), m_aParts.end());
    m_aAttractors.erase(m_aAttractors.begin(), m_aAttractors.end());
}
/*
//--------------------------------------------------------------
void ofxParticleWorld::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofxParticleWorld::keyReleased(int key){

}

//--------------------------------------------------------------
void ofxParticleWorld::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofxParticleWorld::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxParticleWorld::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofxParticleWorld::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofxParticleWorld::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofxParticleWorld::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofxParticleWorld::dragEvent(ofDragInfo dragInfo){

}
*/
