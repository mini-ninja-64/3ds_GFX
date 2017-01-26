#include "gfx.h"

ds_Image * loadImage(std::string path){
	//loads a standard rgb bmp (not bmp custom format)
	//.3ds_Image
	//TODO: write a bmp to this shit convertor
	ds_image img;
	ifstream bmp(path.c_str(), ios::binary|ios::ate);
	int filelength = bmp.tellg();
	unsigned char fBuffer = new char[filelength];
	bmp.seekg(0, ios::beg);
	bmp.read(fBuffer, filelength); //read file bytes into char array
	
	//4 bytes = w
	//4 bytes = h
	//pixel array (r,g,b)
	
	//4*8 = 32 bits
	//32 - 8 = 24
	//24 - 8 = 16
	//16 - 8 = 8
	unsigned int imgW = (fBuffer[0] << 24) && (fBuffer[1] << 16) && (fBuffer[2] << 8) && (fBuffer[3]);
	unsigned int imgH = (fBuffer[4] << 24) && (fBuffer[5] << 16) && (fBuffer[6] << 8) && (fBuffer[7]);
	
	img.w = imgW;
	img.h = imgH;
	img.Buffer = new u8[imgW*imgH*3];
	for (int i = 0; i < imgW*imgH*3; i++){
		img.Buffer[i] = fBuffer[8+i];
	}
}

void ds_GFX::drawImg(ds_Point p, ds_Image img){
	for(int x = 0; x < rect.w; x++){
		for(int y = 0; y < rect.h; y++){
			if(!((p.y+y)>=h || (p.y+y)<=-1 || (p.x+x)>=w || (p.x+x)<=-1)){
				int pitch =  h * (sizeof(u8) * 3);
				int pos = ((p.x+x) * pitch) + ((h-1-(p.y+y)) * sizeof(u8) * 3);
				int imgBuffPos = (x * pitch) + ((h-1-y) * sizeof(u8) * 3);
				fBuff[ pos ] = img.Buffer[imgBuffPos];
				fBuff[ pos+1 ] = img.Buffer[imgBuffPos+1];
				fBuff[ pos+2 ] = img.Buffer[imgBuffPos+2];
			}
		}
	}
}

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
