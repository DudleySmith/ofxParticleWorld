//
//  ofxConstraint.cpp
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 12/01/2014.
//
//

#include "ofxConstraint.h"


// -----------------------------------------------------------------------
ofxConstraint::ofxConstraint(){
    
}

// -----------------------------------------------------------------------
ofxConstraint::~ofxConstraint(){
    
}

// -----------------------------------------------------------------------
void ofxConstraint::draw()
{
    if(m_eType==CONSTRAINT_POINT || m_eType==CONSTRAINT_LINE){
        ofNoFill();
        ofCircle(m_oPt1, 10);
        ofFill();
        ofCircle(m_oPt1, 4);
    }

    if(m_eType==CONSTRAINT_LINE){
        ofNoFill();
        ofCircle(m_oPt2, 10);
        ofFill();
        ofCircle(m_oPt2, 4);
    
        ofLine(m_oPt1, m_oPt2);
    }
    
}

// -----------------------------------------------------------------------
void ofxConstraint::setPoint(ofPoint _P1){
    m_oPt1 = _P1;
    m_oPt2 = _P1;
}

// -----------------------------------------------------------------------
void ofxConstraint::setLine(ofPoint _P1, ofPoint _P2){
    m_oPt1 = _P1;
    m_oPt2 = _P2;
}

// -----------------------------------------------------------------------
ofVec3f ofxConstraint::shortDistance(ofVec3f _pt){

    /*
     Origin algorithm
     float minimum_distance(vec2 v, vec2 w, vec2 p) {
     // Return minimum distance between line segment vw and point p
     const float l2 = length_squared(v, w);  // i.e. |w-v|^2 -  avoid a sqrt
     if (l2 == 0.0) return distance(p, v);   // v == w case
     // Consider the line extending the segment, parameterized as v + t (w - v).
     // We find projection of point p onto the line.
     // It falls where t = [(p-v) . (w-v)] / |w-v|^2
     const float t = dot(p - v, w - v) / l2;
     if (t < 0.0) return distance(p, v);       // Beyond the 'v' end of the segment
     else if (t > 1.0) return distance(p, w);  // Beyond the 'w' end of the segment
     const vec2 projection = v + t * (w - v);  // Projection falls on the segment
     return distance(p, projection);
     }
     */
    ofVec3f v=getPt1();
    ofVec3f w=getPt2();

    // Return minimum distance between line segment vw and point p
    float l2 = getLine().lengthSquared();  // i.e. |w-v|^2 -  avoid a sqrt
    if (l2 == 0.0) return _pt - v;   // v == w case
    // Consider the line extending the segment, parameterized as v + t (w - v).
    // We find projection of point p onto the line.
    // It falls where t = [(p-v) . (w-v)] / |w-v|^2
    float t = (_pt - v).dot(w - v) / l2;
    if (t < 0.0) return v-_pt;       // Beyond the 'v' end of the segment
    else if (t > 1.0) return w-_pt;  // Beyond the 'w' end of the segment
    ofVec3f projection = v + t * (w - v);  // Projection falls on the segment

    return projection-_pt;

}

