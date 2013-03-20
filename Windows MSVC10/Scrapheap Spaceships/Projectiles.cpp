//
//  Projectiles.cpp
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 17.03.13.
//
//

#include "Projectiles.h"

Projectiles::Projectiles() {
    speed = 7;
}

bool Projectiles::isLive() {
    return live;
}

void Projectiles::setLive(bool isLive) {
    live = isLive;
}

int Projectiles::getID() {
    return ID;
}

void Projectiles::setID(int iVal) {
    ID = iVal;
}

float Projectiles::getX() {
    return x;
}

void Projectiles::setX(float xVal) {
    x = xVal;
}

float Projectiles::getY() {
    return y;
}

void Projectiles::setY(float yVal) {
    y = yVal;
}

float Projectiles::getSpeed() {
    return speed;
}

void Projectiles::setSpeed(float sVal) {
    speed = sVal;
}