#ifndef gfx_h
#define gfx_h

#include <3ds.h>
#include <iostream>
#include <string.h>

#include <fstream>
#include <sstream>



struct ds_Image
{
	int w;
	int h;
	u8 * Buffer;
};

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

bool operator==(const ds_Col& lhs, const ds_Col& rhs);

ds_Image loadImage(const u8 * fileArray);

class ds_GFX
{
public:
	void init();

	void putPixel(ds_Point p, ds_Col col);

	void drawImage(ds_Point p, ds_Image * img);
	void drawImage(ds_Point p, ds_Image * img, ds_Col trans); //coz i'm lazy and didnt wanna support transparency
	
	//lines
	void line(ds_Point p0, ds_Point p1, ds_Col col);
	
	//filled shapes
	void rectFill(ds_Rect rect, ds_Col col);
	//void circleFill(ds_Point p, ds_Col col);
	
	//line shapes
	void rect(ds_Rect rect, ds_Col col);
	void circle(ds_Point p, ds_Col col, int r);
	
	//wierd shapes
	void drawText(std::string text, ds_Col fg, ds_Col bg); //TODO-simple ascii text renderer


	void clear(ds_Col col);

	void beginFrame(gfxScreen_t scr);

	void pushFrame();

	//data access
	int getWidth();
	int getHeight();
	int textScale;
	ds_Point textCursor;
	u8* fBuff;
private:
	bool top;

	int w;
	int h;
};

#endif /* gfx_h */
