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
#include <allegro5/allegro.h>
#include "OurHero.h"
#include "Projectiles.h"

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
    
private:
    OurHero *hero; // This is our playable hero :D
    Projectiles Projectile[5]; // Our heroes projectiles (for initialization)
    
    enum KEY { UP, DOWN, LEFT, RIGHT, SPACE, SHIFT }; // Holds the values of the current keyboard input
    bool key[6];
    
    bool redraw;
    
    int displayResY, displayResX; // Maximum users monitor resolution
    static const int framesPerSecond = 60;   // Maximum frames per second the game is going to run in
    
    int mouseAxesY, mouseAxesX; // Position of the cursor
    
    void getDisplayResolution(); // Get users max resolution
    
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eQueue;
    ALLEGRO_EVENT *event;
    ALLEGRO_TIMER *timer;
};

#endif /* defined(__Scrapheap_Starships__BasicGameEngine__) */
