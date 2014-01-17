//
//  ofxParticleWorldDefine.h
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 08/01/2014.
//
//

#pragma once

#include "ofMain.h"

enum partAttractorMode{
	PATTRACTOR_ATTRACT = 0,
	PATTRACTOR_REPEL,
	PATTRACTOR_NOISE
};

enum partRenderMode{
    PRENDER_NoRender = 0
    ,PRENDER_QUAD = 1
    ,PRENDER_SQUARE = 2
    ,PRENDER_DISC = 3
    ,PRENDER_CIRCLE = 4
    ,PRENDER_3RONDS = 5
    ,PRENDER_TRAIT = 6
    ,PRENDER_CROIX = 7
    ,PRENDER_X = 8
    ,PRENDER_HEXAGON = 9
    ,PRENDER_PENTAGON = 10
    ,PRENDER_OCTOGON = 11
    ,PRENDER_CAT = 12
    ,PRENDER_LETTRE = 13
    ,PRENDER_OBLIQU = 14
};


enum partColorMode{
	PCOLOR_MODE_CREATION = 0,
	PCOLOR_MODE_LIFE,
	PCOLOR_MODE_VEL
};

