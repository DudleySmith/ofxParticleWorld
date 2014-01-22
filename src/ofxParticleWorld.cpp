
#include "ofxParticleWorld.h"

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
    m_pgWorld.add(m_pxFpsSaveMax.set("FpsMax", 20, 0, 60));
    m_pgWorld.add(m_pxFpsSaveMin.set("FpsMin", 12, 0, 60));
    m_pgWorld.add(m_pxZMax.set("ZMax", 1, 0, 100));
    
    m_pgParts.setName("Parts");
    m_pgParts.add(m_pxSize.set("Size", 0, 1, 20));
    m_pgParts.add(m_pxRateSize.set("RateSize", 0, 0, 1));
    m_pgParts.add(m_pxLifeBase.set("LifeBase", 1, 0, 20));
    m_pgParts.add(m_pxLifeReal.set("LifeReal", 1, 0, 20));
    m_pgParts.add(m_pxEternalLife.set("IsEternalLife", 0));
    
    m_pgAttractions.setName("Attractions");
    m_pgAttractions.add(m_pxCoefForces.set("CoefForces", 0.4, 0, 2));
    m_pgAttractions.add(m_pxCoefForcesMin.set("CoefForcesMin", 0.05, 0, 0.1));
    m_pgAttractions.add(m_pxCoefForces_X.set("CoefForces_X", 0, 0, 1));
    m_pgAttractions.add(m_pxCoefForces_Y.set("CoefForces_Y", 0, 0, 1));
    m_pgAttractions.add(m_pxDrag.set("Drag", 0.5, 0, 1));
    m_pgAttractions.add(m_pxDistMin.set("DistMin", 40, 0, 250));
    m_pgAttractions.add(m_pxDistMax.set("DistMax", 300, 0, 1000));
    m_pgAttractions.add(m_pxMaxProxCounter.set("MaxProxCounter", 500, 0, 1000));
    
    m_pgEmissions.setName("Emissions");
    m_pgEmissions.add(m_pxPulse.set("Pulse", 0.5, 0, 1));
    m_pgEmissions.add(m_pxFlowBase.set("FlowBase", 40, 0, 200));
    m_pgEmissions.add(m_pxFlowReal.set("FlowReal", 40, 0, 200));

    m_pgSets.add(m_pgWorld);
    m_pgSets.add(m_pgParts);
    m_pgSets.add(m_pgAttractions);
    m_pgSets.add(m_pgEmissions);
    
}

//------------------------------------------------------------------
void ofxParticleWorld::setAttractors(vector<ofxAttractor> *attract){
	m_pAttractors = attract;
}

//--------------------------------------------------------------
void ofxParticleWorld::update(){
    
    vector<ofxParticle>::iterator   oneParticle;
    
    for(oneParticle = m_aParts.begin(); oneParticle != m_aParts.end(); ++oneParticle){
        
        (*oneParticle).setAttractPoints(m_pAttractors);
        
        if(getPxEternalLife()==false && (*oneParticle).isDead(getLife()) == true){
            oneParticle = m_aParts.erase(oneParticle);
        }else{
            (*oneParticle).update();
        }
        
        if(oneParticle == m_aParts.end())   break;

    }
    
    // Update of label for real life used
    m_pxLifeReal = getLife();
    m_pxFlowReal = getFlow();
    
}

//--------------------------------------------------------------
void ofxParticleWorld::draw(){
    
    vector<ofxParticle>::iterator   oneParticle;

    for(oneParticle = m_aParts.begin(); oneParticle != m_aParts.end(); oneParticle++){
        (*oneParticle).draw();
	}
}


//--------------------------------------------------------------
void ofxParticleWorld::clear(){
    m_aParts.erase(m_aParts.begin(), m_aParts.end());
}

//--------------------------------------------------------------
float ofxParticleWorld::getFpsSaveRate(){
    float rate = ofMap(ofGetFrameRate(), m_pxFpsSaveMin, m_pxFpsSaveMax, 0, 1, true);

    return rate*rate;
    
}

//--------------------------------------------------------------
float ofxParticleWorld::getFlow(){
    return m_pxFlowBase * getFpsSaveRate();
}

//--------------------------------------------------------------
float ofxParticleWorld::getLife(){
    return m_pxLifeBase * getFpsSaveRate();
}

//--------------------------------------------------------------
vector<ofxParticle> ofxParticleWorld::getTrackers(){
    return m_aParts;
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
