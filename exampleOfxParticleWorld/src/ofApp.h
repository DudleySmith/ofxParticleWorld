#pragma once

#include "ofMain.h"
#include "ofxParticleWorld.h"
#include "ofxGui.h"
#include "ofxColorSet.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
    ofxParticleWorld m_oWorld;
    string          currentModeStr;
    
    ofxPanel         uiParts;
    ofParameterGroup gpParts;
    
    ofxPanel         uiColors;
    ofParameterGroup gpColors;
    ofxButton        btReload;
    
    ofPoint          ptStart;
    ofPoint          ptEnd;
    map <string, ofxEmitter>     m_aEmitters;
    
    ofxLabel         fps;
    ofxLabel         nbParts;
    ofxLabel         dist;
    
    ofxColorSet      m_oColorSet;
    
    
};
