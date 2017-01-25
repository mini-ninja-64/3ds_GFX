#include "gfx.h"

void ds_GFX::init(){
	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);
}

void ds_GFX::beginFrame(gfxScreen_t scr){
	if(scr == GFX_TOP){
		top = true;

		w = 400;
		h = 240;
	}else{
		top = false;
		
		w = 320;
		h = 240;
	}
	fBuff = gfxGetFramebuffer(scr, GFX_LEFT, NULL/*W*/, NULL/*H*/);
}

void ds_GFX::pushFrame(){
	gfxFlushBuffers();	
	gfxSwapBuffers();
	gspWaitForVBlank();
}

void ds_GFX::putPixel(int x,int y, ds_Col col){
	if(!(y>=h || y<=-1 || x>=w || x<=-1)){
		int pitch =  h * (sizeof(u8) * 3);
		int pos = (x * pitch) + ((h-1-y) * sizeof(u8) * 3);
		fBuff[ pos ] = col.b;
		fBuff[ pos+1 ] = col.g;
		fBuff[ pos+2 ] = col.r;
	}
}

void ds_GFX::clear(ds_Col col){
	if (((col.r - col.g) - col.b) == -col.r){ //if all equal in astrange way for no paticular reason :)
		memset(fBuff, ((col.b & 0xff) << 16) + ((col.g & 0xff) << 8) + (col.r & 0xff), h*w*3);
	}else{
		for (int i = 0; i < w*h*3; i+=3){
			fBuff[i] = col.b;
			fBuff[i+1] = col.g;
			fBuff[i+2] = col.r;
		}
	}
}