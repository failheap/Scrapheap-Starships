//
//  OurHero.h
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 17.03.13.
//
//

#ifndef __Scrapheap_Starships__OurHero__
#define __Scrapheap_Starships__OurHero__

#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "OurEntity.h"
#include "Projectiles.h"

class OurHero : public OurEntity {
public:
    OurHero(float posX, float posY);
    
    int getHealth(); // Returns health
    void setHealth(int hValue); //Sets value of health
    
    int getAmmoCount(); // Returns remaining ammo
    void setAmmoAmount(int aValue); // Adds ammo to inventory
    
    float getStamina(); // Returns how much stamina the player has left
    void setStamina(float sValue); // Sets player stamina
    
    /*
     
     Projectile functions
     
     Handles projectile mechanics when player uses his weapon
     
     */
    
    int projectileHeadingX, projectileHeadingY; // Stores the position of mouse pointer so we know which direction out hero is shooting at'
    
    void initProjectile(Projectiles projectile[], int size);
    void drawProjectile(Projectiles projectile[], int size);
    void fireProjectile(Projectiles projectile[], int size, int mPosX, int mPosY);
    void updateProjectile(Projectiles projectile[], int size, int boundX, int boundY);

private:
    int health, ammo;
    float stamina;
};

#endif /* defined(__Scrapheap_Starships__OurHero__) */
