#include <3ds.h>
#include <iostream>
#include <string.h>
#include "gfx.h"

int main(int argc, char **argv) {
	int x = 0;
	int y = 0;
	ds_GFX gfx;
	ds_Col bg = {255,0,0};
	ds_Col fg = {0,0,0};
	gfx.init();
    while(aptMainLoop()) {

        hidScanInput();
        if(hidKeysDown() & KEY_START) {
            break;
        }
        if (hidKeysDown() & KEY_DUP) {
        	y--;
        }
        if (hidKeysDown() & KEY_DDOWN) {
        	y++;
        }
        if (hidKeysDown() & KEY_DRIGHT) {
        	x++;
        }
        if (hidKeysDown() & KEY_DLEFT) {
        	x--;
        }

        //screen clear
        gfx.beginFrame(GFX_TOP);

        gfx.clear(bg);
        gfx.putPixel(x,y,fg);
        //std::cout << x << ',' << y << ',' << gfx.w << ',' << gfx.h << std::endl;
        gfx.pushFrame();
    }

    gfxExit();
    return 0;
}