#include "mainScreen.h"

void mainScreen::init(ds_GFX gfx){

}

void mainScreen::input(ds_GFX gfx){

}

void mainScreen::update(ds_GFX gfx){

}

void mainScreen::draw(ds_GFX gfx){
	gfx.beginFrame(GFX_TOP);
	gfx.clear((ds_Col){0,0,0});
	gfx.rectFill((ds_Rect){0,0,5,5},(ds_Col){255,0,0});
	gfx.rectFill((ds_Rect){0,0,2,2},(ds_Col){0,255,0});
	gfx.rectFill((ds_Rect){0,0,1,1},(ds_Col){0,0,255});
}