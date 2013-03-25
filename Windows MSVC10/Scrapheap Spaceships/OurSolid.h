//
//  OurSolid.h
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 24.03.13.
//
//
// Header file for class OurSolid:
//
// Represents a static solid, non-interactive object in the game world
// example: wall, decoration or other solid entities

#ifndef __Scrapheap_Starships__OurSolid__
#define __Scrapheap_Starships__OurSolid__

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <sstream>
#include <fstream>

#include "OurEntity.h"

class OurSolid : public OurEntity {
public:
	OurSolid(float posX, float posY, const char *bitmap);
	~OurSolid();

	void drawSolid();
private:
	ALLEGRO_BITMAP *solidGraph;
	float xPos, yPos;
};

#endif /* defined(__Scrapheap_Starships__OurSolid__) */