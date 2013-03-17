//
//  OurEntity.cpp
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 17.03.13.
//
//

#include "OurEntity.h"

OurEntity::OurEntity(float posX, float posY) {
    positionX = posX;
    positionY = posY;
}

float OurEntity::getPosX() {
    return positionX;
}

float OurEntity::getPosY() {
    return positionY;
}

void OurEntity::setPosX(float pos) {
    positionX = pos;
}

void OurEntity::setPosY(float pos) {
    positionY = pos;
}

void OurEntity::update() {
    al_draw_filled_rectangle(positionX, positionY, positionX + 30, positionY + 30, al_map_rgb(255, 0, 255));
}

void OurEntity::setSpeed(int sVal) {
    speed = sVal;
}

int OurEntity::getSpeed() {
    return speed;
}