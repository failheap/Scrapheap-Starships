//
//  GameInterface.cpp
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 16.03.13.
//
//

#include "GameInterface.h"

GameInterface::GameInterface(int screenY, int screenX, int gameState) {
    resX = screenX;
    resY = screenY;
    state = gameState;
    menuChoice = 0;
}

GameInterface::~GameInterface() {
    
}

void GameInterface::drawMainMenu() {
    
}

int GameInterface::getMenuChoice() {
    return menuChoice;
}

void GameInterface::setMenuChoice(int choice) {
    menuChoice = choice;
}