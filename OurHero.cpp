//
//  OurHero.cpp
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 17.03.13.
//
//

#include "OurHero.h"

OurHero::OurHero(float posX, float posY)
: OurEntity(posX, posY) {
    
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
            
            if (projectile[i].getX() == projectileHeadingX && projectile[i].getY() == projectileHeadingY)
                projectile[i].setLive(false);
            
            if (projectile[i].getX() > boundX || projectile[i].getY() > boundY)
                projectile[i].setLive(false);
            
        }
    }
}