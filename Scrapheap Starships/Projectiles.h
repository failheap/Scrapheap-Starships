//
//  Projectiles.h
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 17.03.13.
//
//

#ifndef __Scrapheap_Starships__Projectiles__
#define __Scrapheap_Starships__Projectiles__

#include <allegro5/allegro.h>

class Projectiles {
public:
    Projectiles();
    
    bool isLive();
    void setLive(bool isLive);
    
    int getID();
    void setID(int iVal);
    
    float getX();
    void setX(float xVal);
    
    float getY();
    void setY(float yVal);
    
    float getSpeed();
    void setSpeed(float sVal);
    
    
private:
    int ID;
    float x,y,speed = 7;
    bool live;
};

#endif /* defined(__Scrapheap_Starships__Projectiles__) */
