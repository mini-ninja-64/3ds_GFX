#include "gfx.h"

void ds_GFX::init(){
	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);
}

void ds_GFX::rectFill(ds_Rect rect, ds_Col col){
	for(int x = 0; x < rect.w; x++){
		for(int y = 0; y < rect.h; y++){
			putPixel((ds_Point){x+rect.x,y+rect.y},col);
		}
	}
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

void circle(ds_Point p, ds_Col col, int r)
	unsigned int x= r0, y= 0;//local coords
	int cd2= 0;  //current distance squared - radius squared

	int xc = p.x; int yc = p.y;

	if (!r0) return;
	putPixel((ds_Point){xc-r0, yc}, col);
	putPixel((ds_Point){xc+r0, yc}, col);
	putPixel((ds_Point){xc, yc-r0}, col);
	putPixel((ds_Point){xc, yc+r0}, col);

	while (x > y)    //only formulate 1/8 of circle
	{
		cd2-= (--x) - (++y);
		if (cd2 < 0) cd2+=x++;

		putPixel((ds_Point){xc-x, yc-y}, col);//upper left left
		putPixel((ds_Point){xc-y, yc-x}, col);//upper upper left
		putPixel((ds_Point){xc+y, yc-x}, col);//upper upper right
		putPixel((ds_Point){xc+x, yc-y}, col);//upper right right
		putPixel((ds_Point){xc-x, yc+y}, col);//lower left left
		putPixel((ds_Point){xc-y, yc+x}, col);//lower lower left
		putPixel((ds_Point){xc+y, yc+x}, col);//lower lower right
		putPixel((ds_Point){xc+x, yc+y}, col);//lower right right
	}
}

void ds_GFX::putPixel(ds_Point p, ds_Col col){
	if(!(p.y>=h || p.y<=-1 || p.x>=w || p.x<=-1)){
		int pitch =  h * (sizeof(u8) * 3);
		int pos = (p.x * pitch) + ((h-1-p.y) * sizeof(u8) * 3);
		fBuff[ pos ] = col.b;
		fBuff[ pos+1 ] = col.g;
		fBuff[ pos+2 ] = col.r;
	}
}

void ds_GFX::clear(ds_Col col){
	if (((col.r - col.g) - col.b) == -col.r){ //if all equal in astrange way for no paticular reason :)
		memset(fBuff, col.r, h*w*3);
	}else{
		for (int i = 0; i < w*h*3; i+=3){
			fBuff[i] = col.b;
			fBuff[i+1] = col.g;
			fBuff[i+2] = col.r;
		}
	}
}
