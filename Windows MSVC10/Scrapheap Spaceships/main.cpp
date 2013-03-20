#define ALLEGRO_STATICLINK

#include <allegro5/allegro.h>
#include "BasicGameEngine.h"

int main(int argc, char **argv) {
    BasicGameEngine *engine = new BasicGameEngine;
    engine->start(); // Initializes engine and starts the application loop
    delete engine;
    return 0;
}