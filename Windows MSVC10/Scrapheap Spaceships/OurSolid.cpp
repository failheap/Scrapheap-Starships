#include "OurSolid.h"


OurSolid::OurSolid(float posX, float posY, const char *bitmap) 
: OurEntity(posX, posY) {
	xPos = posX;
	yPos = posY;

	al_init_image_addon();
	solidGraph = al_load_bitmap(bitmap);
}


OurSolid::~OurSolid() {
	al_destroy_bitmap(solidGraph);
}

void OurSolid::drawSolid() {
	al_draw_bitmap(solidGraph, xPos, yPos, ALLEGRO_VIDEO_BITMAP);  // Enable hardware acceleration for these solids
}