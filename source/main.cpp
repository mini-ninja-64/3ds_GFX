#include <3ds.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "mainScreen.h"

u8* buffer;

int main(int argc, char **argv) {
	int x = 0;
	int y = 0;
	ds_GFX gfx;
	ds_Col bg = {255,0,0};
	ds_Col fg = {0,0,0};
	gfx.init();
	mainScreen mscr;
	mscr.init(gfx);

    while(aptMainLoop()) {
        hidScanInput();
        if(hidKeysDown() & KEY_START) {
            break;
        }
        mscr.input(gfx);
        mscr.update(gfx);
        mscr.draw(gfx);
        
        gfx.pushFrame();
    }

    gfxExit();
    return 0;
}