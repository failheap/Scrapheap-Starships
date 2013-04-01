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
    hero = new OurHero(50, 50);
    
    // Initialize 5 projectiles for our hero
     
    hero->initProjectile(Projectile, 5);
    
    // Get X/Y position of player
    
    float pos_y = hero->getPosY();
    float pos_x = hero->getPosX();
    
    // Maximum speed player can move (value = pixel pr. second)
    
    hero->setSpeed(3);

	// Generate our map

	map = new OurMap(10,10);
    
    // Initiate main game loop
    
    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(eQueue, &ev);
        
        if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseAxesX = ev.mouse.x;
            mouseAxesY = ev.mouse.y;
        }
        
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    key[UP] = true;
					cameraUpdate = true;
                    break;
                case ALLEGRO_KEY_S:
                    key[DOWN] = true;
					cameraUpdate = true;
                    break;
                case ALLEGRO_KEY_D:
                    key[RIGHT] = true;
					cameraUpdate = true;
                    break;
                case ALLEGRO_KEY_A:
                    key[LEFT] = true;
					cameraUpdate = true;
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
					cameraUpdate = false;
                    break;
                case ALLEGRO_KEY_S:
                    key[DOWN] = false;
					cameraUpdate = false;
                    break;
                case ALLEGRO_KEY_D:
                    key[RIGHT] = false;
					cameraUpdate = false;
                    break;
                case ALLEGRO_KEY_A:
                    key[LEFT] = false;
					cameraUpdate = false;
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
            
            // If player holds shift, increse speed by 2 pixels/s
            // this simulates run, but will drain players stamina
            // stamina will regenerate at 30% / s when the player
            // is not running
            
            if (key[SHIFT] && hero->getStamina() > 0) {
                pos_y -= key[UP] * (hero->getSpeed() + 4);
                pos_y += key[DOWN] * (hero->getSpeed() + 4);
                pos_x -= key[LEFT] * (hero->getSpeed() + 4);
                pos_x += key[RIGHT] * (hero->getSpeed() + 4);
                hero->setStamina(hero->getStamina() - 1);
                
            } else {
                pos_y -= key[UP] * hero->getSpeed();
                pos_y += key[DOWN] * hero->getSpeed();
                pos_x -= key[LEFT] * hero->getSpeed();
                pos_x += key[RIGHT] * hero->getSpeed();
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
            
            // Update player position
            
            hero->setPosX(pos_x);
            hero->setPosY(pos_y);
			hero->setAngle(atan2(float(mouseAxesY - pos_y),float(mouseAxesX - pos_x))); // Radiens = arc tangent of mouseAxesX/Y - Player positionX/Y
																						// Set angle for player rotation on hero->update()
            hero->update();

			// Update camera position

			map->setOffsetX(0);
			map->setOffsetY(0);

			map->setOffsetX(map->getOffsetX() - (screenW / 2) + (pos_x + hero->getPBitmapWidth() / 2));
			map->setOffsetY(map->getOffsetY() - (screenH / 2) + (pos_y + hero->getPBitmapHeight() / 2));

			if (map->getOffsetX() < 0)
				map->setOffsetX(0);
			if (map->getOffsetY() < 0)
				map->setOffsetY(0);

			al_identity_transform(&camera);
			al_translate_transform(&camera, -map->getOffsetX(), -map->getOffsetY());
			al_use_transform(&camera);
            
            // Draw projectiles if projectiles are fired
            hero->drawProjectile(Projectile, 5);
            
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));

        }

    }

	delete map;
}