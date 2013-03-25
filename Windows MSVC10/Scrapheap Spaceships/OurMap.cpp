//
//  OurMap.cpp
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 21.03.13.
//
//

#include "OurMap.h"

using namespace std;


OurMap::OurMap(int height, int width) {
	tileSize = 200;

	mapHeight = height;
	mapWidth = width;

	al_init_image_addon();
	al_init_primitives_addon();
	
	generateMap();
	loadTextures();
}


OurMap::~OurMap() {
	for (int i = 0; i < solids.size(); i++) {
		delete solids[i];
	}
}

void OurMap::draw() {

	/*
		Loop through the map vector to determine what 
		should be drawn on the screen
	*/

	for (int i = 0; i < map.size(); i++) {
		for (int x = 0; x < map[i].size(); x++) {
			if (map[i][x] == 0) { // A value of 0 means the default texture
				for (int y = 0; y < solids.size(); y++) {
					solids[y]->drawSolid();
				}
			} else {
				al_draw_line(x * tileSize, i * tileSize, x * (tileSize * 2), i * (tileSize * 2), al_map_rgb(255,255,255), 1); 
			}
		}
	}
}

int OurMap::getOffsetX() {
	return xOffset;
}

int OurMap::getOffsetY() {
	return yOffset;
}

void OurMap::setOffsetX(int offset) {
	xOffset = offset;
}

void OurMap::setOffsetY(int offset) {
	yOffset = offset;
}

void OurMap::generateMap() {
	std::vector<int> temporaryVectorRow;	// A temporary vector holding one row at a time
	TwoDimIntegerVector roomSize;			// A vector storing the size of the room
	bool previousBlockIsSolid = false;		// Stores boolean value if previous block was solid (> 0)

	for (int i = 0; i < mapHeight; i++) {
		temporaryVectorRow.clear(); // Clear our tmp vector for new insert

		/* 
			The first and last row of the vector we generate empty tiles,
			so we don't get walls plastered right up at the edge of the map
		*/

		if (i == 0 || i == mapHeight - 1) {
			for (int x = 0; x < mapWidth; x++) {
				temporaryVectorRow.push_back(0);
			}
			map.push_back(temporaryVectorRow);

		/*
			If this is not the first or last line of map vector, we can
			begin generating random values for map
		*/

		} else {
			srand(time(NULL)); // Random number seed
			for (int x = 0; x < mapWidth; x++) {
				/*
					If this is the first or last column, generate an empty tile so we don't
					get walls plastered at the left or right edge of the map either
				*/
				if (x == 0 || x == mapWidth - 1) {
					temporaryVectorRow.push_back(0);
				} else {
					temporaryVectorRow.push_back(rand()%2);
					if (previousBlockIsSolid) {
						
					} else {
						
					}
				}
			}
			map.push_back(temporaryVectorRow);
			temporaryVectorRow.clear();
		}
	}
}

void OurMap::loadTextures() {
	ifstream tFile("textures.ifile", ifstream::in); // open file which contains a list off all the textures used in-game
	string tLine;
	if (tFile.is_open()) {
		int linePos = 0;
		while (!tFile.eof()) {	// read through each line and feed them into string tLine
			getline(tFile, tLine);
			for (int i = 0; i < map.size(); i++) {
				for (int x = 0; x < map[i].size(); x++) {
					if (map[i][x] == linePos) { // If the key number in textfile (e.g line number) equals map vectors integer create new 
												// object for that square, and give it the current value in line number as the graphic
						OurSolid *solid = new OurSolid(x * tileSize, i * tileSize, tLine.c_str());
						solids.push_back(solid);
					} 
				}
			}
			linePos ++;
		}
	} else { //if we can't find or open the texture datafile, throw rudamentary error message
		al_show_native_message_box(NULL, NULL, NULL,
			"Error reading texture database", NULL, NULL);
	}
	tFile.close();
}