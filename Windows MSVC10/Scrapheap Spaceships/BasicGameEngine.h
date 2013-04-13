//
//  BasicGameEngine.h
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 16.03.13.
//
//

#ifndef __Scrapheap_Starships__BasicGameEngine__
#define __Scrapheap_Starships__BasicGameEngine__

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include "OurHero.h"
#include "Projectiles.h"
#include "OurMap.h"

/* 
 
 Basic game engine class:
 
 The god class (makes stuff happen)
 
 */

class BasicGameEngine {
public:
    BasicGameEngine();
    ~BasicGameEngine();
    
    void setDisplayResolution(int x, int y); // Sets window size
    void wait(double seconds);
    void start(); // Start the game loop
    
    bool done; // Program loop state

	/*
		Debug function: outputs value in console
		window
	*/

	void engineDebug(int dVal) {
		std::cout <<dVal;
	}

	void engineDebug(float dVal) {
		std::cout <<dVal;
	}

	void engineDebug(char dVal) {
		std::cout <<dVal;
	}

	void engineDebug(std::string dVal) {
		std::cout <<dVal;
	}
    
private:
    OurHero *hero; // This is our playable hero :D
    Projectiles Projectile[5]; // Our heroes projectiles (for initialization)
	OurMap *map; // Map initialization and generation object
    
    enum KEY { UP, DOWN, LEFT, RIGHT, SPACE, SHIFT }; // Holds the values of the current keyboard input
    bool key[6];
    
    bool redraw;
    
    int displayResY, displayResX; // Maximum users monitor resolution
    static const int framesPerSecond = 60;   // Maximum frames per second the game is going to run in
    
    float mouseAxesY, mouseAxesX; // Position of the cursor & its pointers
	float *mouseAxesY_p, *mouseAxesX_p;

	int screenW, screenH; // Screen width + height

	float playerPositionX, playerPositionY;	// values & pointers to players X/Y position in the gameworld
	float *playerPositionX_p, *playerPositionY_p; 
    
    void getDisplayResolution(); // Get users max resolution
    
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eQueue;
    ALLEGRO_EVENT *event;
    ALLEGRO_TIMER *timer;
	ALLEGRO_TRANSFORM camera;
};

#endif /* defined(__Scrapheap_Starships__BasicGameEngine__) */
