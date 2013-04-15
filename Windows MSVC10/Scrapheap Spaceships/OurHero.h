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
#include <allegro5\allegro_image.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "OurEntity.h"
#include "Projectiles.h"

class OurHero : public OurEntity {
public:
    OurHero(float posX, float posY);
	~OurHero();
    
    int getHealth(); // Returns health
    void setHealth(int hValue); //Sets value of health
    
    int getAmmoCount(); // Returns remaining ammo
    void setAmmoAmount(int aValue); // Adds ammo to inventory
    
    float getStamina(); // Returns how much stamina the player has left
    void setStamina(float sValue); // Sets player stamina

	// OurHero class gets its own update function, so it can draw custom stuff

	void update();
    
    /*
     
     Projectile functions
     
     Handles projectile mechanics when player uses his weapon
     
     */
    
    int projectileHeadingX, projectileHeadingY; // Stores the position of mouse pointer so we know which direction out hero is shooting at'
    
    void initProjectile(Projectiles projectile[], int size);
    void drawProjectile(Projectiles projectile[], int size);
    void fireProjectile(Projectiles projectile[], int size, int mPosX, int mPosY);
    void updateProjectile(Projectiles projectile[], int size, int boundX, int boundY);

	/*

	Get player image width and height

	*/

	int getPBitmapHeight();
	int getPBitmapWidth();

private:
	ALLEGRO_BITMAP *heroBitmap;

	// Update lighting properties bound with hero
	void updateHeroLights();

    int health, ammo;
	int imageWidth, imageHight; // Stores the W/H values of our hero sprite
    float stamina;
};

#endif /* defined(__Scrapheap_Starships__OurHero__) */
