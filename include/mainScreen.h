#ifndef mainScreen_h
#define mainScreen_h

#include "gfx.h"

class mainScreen{
public:
	void init(ds_GFX gfx);
	void input(ds_GFX gfx);
	void update(ds_GFX gfx);
	void draw(ds_GFX gfx);
private:
	ds_Image backImg;
	ds_Image bill;
	ds_Image rock;

	ds_Point bgP;
	ds_Point billP;
	ds_Point rockP;

	int score;
	bool dead;
};

#endif /* mainScreen_h */
