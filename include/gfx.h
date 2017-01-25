#ifndef gfx_h
#define gfx_h

#include <3ds.h>
#include <iostream>
#include <string.h>

struct ds_Col
{
	u8 r;
	u8 g;
	u8 b;
};

struct ds_Rect
{
	int x;
	int y;
	int w;
	int h;
};

struct u24{
    unsigned int data : 24;
};

class ds_GFX
{
public:
	void init();

	void putPixel(int x,int y, ds_Col col);

	//void line(int x, int y, ds_Col);
	//void rect(ds_Rect rect, ds_Col col);

	void clear(ds_Col col);

	void beginFrame(gfxScreen_t scr);

	void pushFrame();
	int w;
	int h;
private:
	u8* fBuff;
	bool top;
};

#endif /* gfx_h */