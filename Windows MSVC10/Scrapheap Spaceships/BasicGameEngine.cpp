//
//  BasicGameEngine.cpp
//  Scrapheap Starships
//
//  Created by Helge Nordgård on 16.03.13.
//
//

#include "BasicGameEngine.h"

BasicGameEngine::BasicGameEngine() {
	for (int i = 0; i < 6; i++) {
		key[i] = false;
	}

	screenW = 1024;
	screenH = 600;

	redraw = true;

    al_init();												// Initialize allegro engine
	
    done = false;                                           // Initialize program loop state
    display = al_create_display(screenW, screenH);          // Initialize display
    getDisplayResolution();                                 // Get users max resolution
    // al_resize_display(display, displayResX, displayResY);   // Resize window to fit users max resolution
    
    eQueue = al_create_event_queue();                       // Initialize event queue
    
    al_install_keyboard();                                  // Initialize keyboard
    al_install_mouse();                                     // Initialize mouse
    
    timer = al_create_timer(1.0 / framesPerSecond);                 // Initialize game and set interval
    
    al_register_event_source(eQueue, al_get_keyboard_event_source()); // Register keyboard input into the event queue
    al_register_event_source(eQueue, al_get_mouse_event_source());  // Register mouse movement and input into the event queue
    al_register_event_source(eQueue, al_get_display_event_source(display)); // Register events from the display
    al_register_event_source(eQueue, al_get_timer_event_source(timer)); // Lets the timer register events

	// Initialize special pointers for world coordinate calculations

	mouseAxesX_p = &mouseAxesX;
	mouseAxesY_p = &mouseAxesY;

	playerPositionX_p = &playerPositionX;
	playerPositionY_p = &playerPositionY;

	// Set starting coordinates for player

	*playerPositionX_p = 50;
	*playerPositionY_p = 50;
    
}

// Deconstructor

BasicGameEngine::~BasicGameEngine() {
    delete hero;
	al_destroy_timer(timer);
	al_destroy_event_queue(eQueue);
    al_destroy_display(display);
}

/* 
 Gets the maximum available resolution from the
 users monitor. Handy to know when we code
 menu later on when the user can choose the
 resolution himself
 */

void BasicGameEngine::getDisplayResolution() {
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    displayResX = info.x2 - info.x1;
    displayResY = info.y2 - info.y1;
}

void BasicGameEngine::wait(double seconds) {
    al_rest(seconds);
}

/*
 
 BasicGameEngine::Start contains all the nitty gritty
 code where the actual game takes place
 
 */

void BasicGameEngine::start() {
    
    al_start_timer(timer); // Start timer. This operates at the industry standard 60 FPS, see constructor
	hero = new OurHero(*playerPositionX_p, *playerPositionY_p);
    
    // Initialize 5 projectiles for our hero
     
    hero->initProjectile(Projectile, 5);
    
    // Get X/Y position of player

	*playerPositionX_p = hero->getPosX();
	*playerPositionY_p = hero->getPosY();

    // Maximum speed player can move (value = pixel pr. second)
    
    hero->setSpeed(3);

	// Generate our map

	map = new OurMap(10,10);
    
    // Initiate main game loop
    
    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(eQueue, &ev);
        
        if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			*mouseAxesX_p = ev.mouse.x;
			*mouseAxesY_p = ev.mouse.y;
        }
        
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    key[UP] = true;
                    break;
                case ALLEGRO_KEY_S:
                    key[DOWN] = true;
                    break;
                case ALLEGRO_KEY_D:
                    key[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_A:
                    key[LEFT] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    hero->fireProjectile(Projectile, 5, mouseAxesX, mouseAxesY);
                    key[SPACE] = true;
                    break;
                case ALLEGRO_KEY_RSHIFT:
                    key[SHIFT] = true;
                    break;
                case ALLEGRO_KEY_LSHIFT:
                    key[SHIFT] = true;
                    break;
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    key[UP] = false;
                    break;
                case ALLEGRO_KEY_S:
                    key[DOWN] = false;
                    break;
                case ALLEGRO_KEY_D:
                    key[RIGHT] = false;
                    break;
                case ALLEGRO_KEY_A:
                    key[LEFT] = false;
                    break;
                case ALLEGRO_KEY_SPACE:
                    key[SPACE] = false;
                    break;
                case ALLEGRO_KEY_RSHIFT:
                    key[SHIFT] = false;
                    break;
                case ALLEGRO_KEY_LSHIFT:
                    key[SHIFT] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
            }
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        } else if (ev.type == ALLEGRO_EVENT_TIMER) {
            
            // If player holds shift, increse speed by 4 pixels/s
            // this simulates run, but will drain players stamina
            // stamina will regenerate at 30% / s when the player
            // is not running
            
            if (key[SHIFT] && hero->getStamina() > 0) {
				*playerPositionY_p -= key[UP] * (hero->getSpeed() + 4);
				*playerPositionY_p += key[DOWN] * (hero->getSpeed() + 4);
				*playerPositionX_p -= key[LEFT] * (hero->getSpeed() + 4);
				*playerPositionX_p += key[RIGHT] * (hero->getSpeed() + 4);
                hero->setStamina(hero->getStamina() - 1);
                
            } else {
                *playerPositionY_p -= key[UP] * hero->getSpeed();
                *playerPositionY_p += key[DOWN] * hero->getSpeed();
                *playerPositionX_p -= key[LEFT] * hero->getSpeed();
                *playerPositionX_p += key[RIGHT] * hero->getSpeed();
            }
            
            if (!key[SHIFT] && hero->getStamina() < 1000)
                hero->setStamina(hero->getStamina() + 0.3);
            
            // Update projectile
            
            hero->updateProjectile(Projectile, 5, 640, 480);

            
            redraw = true;
        }
        
        
        if (redraw && al_event_queue_is_empty(eQueue)) {
            redraw = false;

			// redraw map sprites

			map->draw();

			// Update camera position

			map->setOffsetX(0);
			map->setOffsetY(0);

			al_use_transform(&camera);
			
			map->setOffsetX(map->getOffsetX() - (screenW / 2) + (*playerPositionX_p + hero->getPBitmapWidth() / 2));
			map->setOffsetY(map->getOffsetY() - (screenH / 2) + (*playerPositionY_p + hero->getPBitmapHeight() / 2));

			if (map->getOffsetX() < 0)
				map->setOffsetX(0);
			if (map->getOffsetY() < 0)
				map->setOffsetY(0);

			// Initialize and transform all coordinates and bitmaps to coincide with camera

			al_identity_transform(&camera);
			al_translate_transform(&camera, -map->getOffsetX(), -map->getOffsetY());
			al_use_transform(&camera);
			

			// Set player rotation and update it on the map

			hero->setAngle(atan2(float(*mouseAxesY_p - *playerPositionY_p + map->getOffsetY()),
				float(*mouseAxesX_p - *playerPositionX_p + map->getOffsetX())));	// Radians = arc tangent of mouseAxesX/Y - Player positionX/Y + map offset X/Y
																					// Set angle for player rotation on hero->update()

			// Update player position
            
			hero->setPosX(*playerPositionX_p);
			hero->setPosY(*playerPositionY_p);

            hero->update();
            
            // Draw projectiles if projectiles are fired
            hero->drawProjectile(Projectile, 5);
            
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));

        }

    }

	delete map;
}