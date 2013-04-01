//
//  OurEntity.h
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 17.03.13.
//
//

#ifndef __Scrapheap_Starships__OurEntity__
#define __Scrapheap_Starships__OurEntity__

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class OurEntity {
public:
    OurEntity(float posX, float posY); // Initializes entity and sets its position at X/Y
    
    float getPosX(); // Returns X position
    float getPosY(); // Returns Y position
	float getAngle(); // Returns the degree value of entity rotation
    int getSpeed(); // Returns current speed the entity is traveling in
    
    void setPosX(float pos); // Sets Position X cordinate
    void setPosY(float pos); // Sets Position Y cordinate
    void setSpeed(int sVal); // Sets speed for entity
	void setAngle(float degree); // Sets the degree in which to rotate entity towards
    
    void update(); // Update entity position
    
    
private:
    float positionX, positionY; // Entitys current position in the game world
	float angle; // The degree value if we need to rotate entity
    int speed; // The speed the entity moves
};

#endif /* defined(__Scrapheap_Starships__OurEntity__) */
