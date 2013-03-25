//
//  OurMap.h
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 21.03.13.
//
//

#ifndef __Scrapheap_Starships__OurMap__
#define __Scrapheap_Starships__OurMap__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <sstream>
#include <fstream>
#include <iostream>

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>

#include "types.h"
#include "OurSolid.h"

class OurMap {
public:
	/*
		Arguments height x width defines the size of the
		map in 200x200 pixel blocks
	*/

	OurMap(int height, int width);
	~OurMap();

	// Setters and getters for map offset values

	int getOffsetX();
	int getOffsetY();
	void setOffsetX(int offset);
	void setOffsetY(int offset);

	void draw();	// Draws the map
private:
	/*
		Initializes textures and feeds the texture vector
		with graphics from the texture file
	*/

	void loadTextures();

	/* 
		Generates random values in map vector for new map.
	*/

	void generateMap();

	/*
		Debug function: outputs generated map values in console
		window
	*/

	void mapDebug() {
		for (int i = 0; i < map.size(); i++) {
			for (int x = 0; x < map[i].size(); x++) {
				std::cout <<map[i][x];
			}
			std::cout <<"\r\n";
		}
	}

	std::vector<OurSolid*> solids; // This vector contains all our solid objects

	TwoDimIntegerVector map; // This vector contains all the numbers which represent tiles

	int xOffset, yOffset; // Where the camera is at the map

	int mapColumns;
	int mapSize;
	int tileSize;

	int mapHeight, mapWidth;
};

#endif /* defined(__Scrapheap_Starships__OurHero__) */