#include "gfx.h"

bool operator==(const ds_Col& lhs, const ds_Col& rhs)
{
	return ((lhs.r == rhs.r) && (lhs.g == rhs.g) && (lhs.b == rhs.b));
}

ds_Image loadImage(const u8 * fileArray){
	//4 bytes = w
	//4 bytes = h
	//pixel array (b,g,r)
	ds_Image img;
	img.w =  (int)((unsigned char)(fileArray[0]) << 24 |	(unsigned char)(fileArray[1]) << 16 | (unsigned char)(fileArray[2]) << 8 | (unsigned char)(fileArray[3]));
	img.h = (int)((unsigned char)(fileArray[4]) << 24 |	(unsigned char)(fileArray[5]) << 16 | (unsigned char)(fileArray[6]) << 8 | (unsigned char)(fileArray[7]));
	img.Buffer = new u8[img.w*img.h*3];
	//memcpy( &img->Buffer[0], &fileArray[8], (img->w*img->h*3) * sizeof( u8 ) );
	for (int i = 0; i < img.w*img.h*3; i++){
		img.Buffer[i] = fileArray[8+i];
	}
	return (img);
}

void ds_GFX::drawImage(ds_Point p, ds_Image * img){
	for(int x = 0; x < img->w; x++){
		for(int y = 0; y < img->h; y++){
			//get pos of pixel col in img
			int pitch =  img->w * (sizeof(u8) * 3);
			int pos = (y * pitch) + (x * sizeof(u8) * 3);
			//get img pixel
			ds_Col c = {img->Buffer[pos+2],img->Buffer[pos+1],img->Buffer[pos]};

			//draw pixel
			putPixel((ds_Point){p.x+x,p.y+y},c);
		}

	}
}

void ds_GFX::drawImage(ds_Point p, ds_Image * img, ds_Col trans){
	for(int x = 0; x < img->w; x++){
		for(int y = 0; y < img->h; y++){
			//get pos of pixel col in img
			int pitch =  img->w * (sizeof(u8) * 3);
			int pos = (y * pitch) + (x * sizeof(u8) * 3);
			//get img pixel
			ds_Col c = {img->Buffer[pos+2],img->Buffer[pos+1],img->Buffer[pos]};
				//std::cout << (int)trans.r << "," << (int)trans.g << "," << (int)trans.b << std::endl;
				//std::cout << (int)c.r << "," << (int)c.g << "," << (int)c.b << std::endl;

			//svcSleepThread(1000000000);	

			if (!(trans == c)){
				//draw pixel
				putPixel((ds_Point){p.x+x,p.y+y},c);
			}
		}

	}
}

//http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C - for speed just copy/paste will implement my self later
void ds_GFX::line(ds_Point p0, ds_Point p1, ds_Col col){
	int x0 = p0.x; int x1 = p1.x;
	int y0 = p0.y; int y1 = p1.y;
	
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
 
	for(;;){
		putPixel((ds_Point){x0,y0}, col);
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

void ds_GFX::init(){
	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);
}

void ds_GFX::rect(ds_Rect rect, ds_Col col){
	line((ds_Point){rect.x,rect.y},(ds_Point){rect.x+rect.w,rect.y},col);
	line((ds_Point){rect.x+rect.w,rect.y},(ds_Point){rect.x+rect.w,rect.y+rect.h},col);
	line((ds_Point){rect.x+rect.w,rect.y+rect.h},(ds_Point){rect.x,rect.y+rect.h},col);
	line((ds_Point){rect.x,rect.y+rect.h},(ds_Point){rect.x,rect.y},col);
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


int ds_GFX::getWidth(){
	return w;
}

int ds_GFX::getHeight(){
	return h;
}

void ds_GFX::pushFrame(){
	gfxFlushBuffers();	
	gfxSwapBuffers();
	gspWaitForVBlank();
}

void ds_GFX::circle(ds_Point p, ds_Col col, int r){
	int x = r;
	int y = 0;//local coords
	int cd2 = 0;  //current distance squared - radius squared

	int xc = p.x; int yc = p.y;

	if (!r) return;
	putPixel((ds_Point){xc-r, yc}, col);
	putPixel((ds_Point){xc+r, yc}, col);
	putPixel((ds_Point){xc, yc-r}, col);
	putPixel((ds_Point){xc, yc+r}, col);

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
