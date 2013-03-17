//
//  GameInterface.h
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 16.03.13.
//
//

#ifndef __Scrapheap_Starships__GameInterface__
#define __Scrapheap_Starships__GameInterface__

#include <allegro5/allegro.h>

/*
 GameInterface Class:
 
 Handles drawing of GUI and signaling for the game engine
 
 */

class GameInterface {
public:
    GameInterface(int screenY, int screenX, int gameState);
    ~GameInterface();
    
    int getMenuChoice();
    void setMenuChoice(int choice);
    
private:
    void drawMainMenu();
    enum {MAIN,OPTIONS,VIDEO,RES,STARTNEW,LOAD};
    int resX, resY; // Current screen resolution
    int state; // Current game state so GameInterface knows what to draw
    int menuChoice; // Current menuchoice if gamestate is in menu
};

#endif /* defined(__Scrapheap_Starships__GameInterface__) */
