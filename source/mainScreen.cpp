#include "mainScreen.h"

void mainScreen::init(ds_GFX gfx){

}

void mainScreen::input(ds_GFX gfx){
	if (hidkeydown() & KEY_A){
		bg.r = rand() % 255;
		bg.g = rand() % 255;
		bg.b = rand() % 255;
	}
}

void mainScreen::update(ds_GFX gfx){

}

void mainScreen::draw(ds_GFX gfx){
	gfx.beginFrame(GFX_TOP);
	gfx.clear(bg);
}
