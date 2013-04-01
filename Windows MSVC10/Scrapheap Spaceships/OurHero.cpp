//
//  OurHero.cpp
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 17.03.13.
//
//

#include "OurHero.h"

#define THRESHOLD 5

OurHero::OurHero(float posX, float posY)
: OurEntity(posX, posY) {
    health = 100;
    ammo = 300;
    stamina = 1000;

	al_init_image_addon();		// Initialize the Allegro graphics library

	// Load the hero sprite and its dimensions

	heroBitmap = al_load_bitmap("hero.png");
	imageWidth = al_get_bitmap_width(heroBitmap);
	imageHight = al_get_bitmap_height(heroBitmap);
}

void OurHero::update() {
	float posX = OurEntity::getPosX(); // Get private data of derived class OurEntity's position X
	float posY = OurEntity::getPosY(); // get private data of derived class OurEntity's position Y
	// al_draw_bitmap(heroBitmap, posX, posY, ALLEGRO_VIDEO_BITMAP);	
																	
	al_draw_rotated_bitmap(heroBitmap, al_get_bitmap_width(heroBitmap) / 2, al_get_bitmap_height(heroBitmap) / 2, posX, posY,
		OurEntity::getAngle(), ALLEGRO_VIDEO_BITMAP);	// Update hero's position with OurEntity's position
														// Enable hardware acceleration for this sprite
}

OurHero::~OurHero() {
	al_destroy_bitmap(heroBitmap);
}

int OurHero::getHealth() {
    return health;
}

void OurHero::setHealth(int hValue) {
    health = health - hValue;
}

int OurHero::getAmmoCount() {
    return ammo;
}

void OurHero::setAmmoAmount(int aValue) {
    ammo = aValue;
}

float OurHero::getStamina() {
    return stamina;
}

void OurHero::setStamina(float sValue) {
    stamina = sValue;
}

void OurHero::initProjectile(Projectiles projectile[], int size) {
    for (int i = 0; i < size; i++) {
        projectile[i].setID(i);
        projectile[i].setSpeed(10);
        projectile[i].setLive(false);
    }
}

void OurHero::drawProjectile(Projectiles projectile[], int size) {
    for (int i = 0; i < size; i++) {
        if (projectile[i].isLive()) {
            al_draw_circle(projectile[i].getX(), projectile[i].getY(), 2, al_map_rgb(255, 255, 255), 2);
        }
    }
}

void OurHero::fireProjectile(Projectiles projectile[], int size, int mPosX, int mPosY) {    
    for (int i = 0; i < size; i++) {
        if (!projectile[i].isLive()) {
            projectileHeadingX = mPosX;
            projectileHeadingY = mPosY;
            projectile[i].setX(getPosX());
            projectile[i].setY(getPosY());
            projectile[i].setLive(true);
            break;
        }
    }

}

void OurHero::updateProjectile(Projectiles projectile[], int size, int boundX, int boundY) {
    for (int i = 0; i < size; i++) {
        if (projectile[i].isLive()) {
            
            double projectile_direction = atan2(projectileHeadingY - projectile[i].getY(), projectileHeadingX - projectile[i].getX());
            projectile[i].setX(projectile[i].getX() + projectile[i].getSpeed()*cos(projectile_direction));
            projectile[i].setY(projectile[i].getY() + projectile[i].getSpeed()*sin(projectile_direction));
            
            if( fabs(projectile[i].getX() - projectileHeadingX) < THRESHOLD && fabs(projectile[i].getY() - projectileHeadingY) < THRESHOLD)
                projectile[i].setLive(false);
            
            if (projectile[i].getX() > boundX || projectile[i].getY() > boundY)
                projectile[i].setLive(false);
            
        }
    }
}

int OurHero::getPBitmapHeight() {
	return al_get_bitmap_width(heroBitmap);
}

int OurHero::getPBitmapWidth() {
	return al_get_bitmap_height(heroBitmap);
}