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

struct ds_Point
{
	int x;
	int y;
};

class ds_GFX
{
public:
	void init();

	void putPixel(ds_Point p, ds_Col col);

	//void line(int x, int y, ds_Col);
	void rectFill(ds_Rect rect, ds_Col col);
	void drawText(std::string text, ds_Col fg, ds_Col bg); //TODO-simple ascii text renderer


	void clear(ds_Col col);

	void beginFrame(gfxScreen_t scr);

	void pushFrame();

	//data access
	int getWidth();
	int getHeight();
	int textScale;
	ds_Point textCursor;
private:
	u8* fBuff;
	bool top;

	int w;
	int h;
};

#endif /* gfx_h */