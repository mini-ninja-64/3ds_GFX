#include "mainScreen.h"

//external files
#include "space_xd_bin.h"
#include "test_bin.h"
#include "billboi_bin.h"
#include "rock_bin.h"


void mainScreen::init(ds_GFX gfx){
	//imgload
	backImg = loadImage(space_xd_bin);
	bill = loadImage(billboi_bin);
	rock = loadImage(rock_bin);
	
	//point load
	billP = (ds_Point){25,0};
	rockP  = (ds_Point){400,0};
	switch(rand()%3){
		case 0:
			rockP.y = 0;
			break;
		case 1:
			rockP.y = 80;
			break;
		case 2:
			rockP.y = 160;
			break;
	}
	bgP = (ds_Point){0,0};

	//score and death
	//std::cout << "Score: " << score << std::endl;
	std::cout << "Press A to play" << std::endl;
	dead = true;
	//change rock col coz cba to load up PS
	for(int i = 0; i < rock.w*rock.h*3; i+=3){
		ds_Col c = {rock.Buffer[i+2],rock.Buffer[i+1],rock.Buffer[i]};
		if (c == (ds_Col){0,0,0}){
			rock.Buffer[i+2] = 0;
			rock.Buffer[i+1] = 0;
			rock.Buffer[i] = 50;
		}
	}

	score = 0;
}

void mainScreen::input(ds_GFX gfx){
	int speed = 8;
	if (!dead){
		if ((hidKeysDown() & KEY_UP) || (hidKeysHeld() & KEY_UP)){
			billP.y-=speed;
			//std::cout << "up" << std::endl;
			if (billP.y < -(bill.h/2))
				billP.y = -(bill.h/2);
		}
		if ((hidKeysDown() & KEY_DOWN) || (hidKeysHeld() & KEY_DOWN)){
			billP.y+=speed;
			//std::cout << "down" << std::endl;
			if (billP.y > (240-(bill.h/2)))
				billP.y = 240-(bill.h/2);
		}
	}else{
		if (hidKeysUp() & KEY_A){
			dead = false;
			std::cout << "Play!" << std::endl;
			score = 0;
			rockP.x = 400;
			switch(rand()%3){
				case 0:
					rockP.y = 0;
					break;
				case 1:
					rockP.y = 80;
					break;
				case 2:
					rockP.y = 160;
					break;
			}
		}
	}
	
	//if finished check for KEY_A up to restart
}

void mainScreen::update(ds_GFX gfx){
	if(!dead){
		if ((rockP.x+rock.w)<0){
			rockP.x = 400;
			switch(rand()%3){
				case 0:
					rockP.y = 0;
					break;
				case 1:
					rockP.y = 80;
					break;
				case 2:
					rockP.y = 160;
					break;
			}
			score++;
		}
		
		if ((rectInRect((ds_Rect){billP.x,billP.y+/*head height*/,bill.w,/*body height*/},(ds_Rect){rockP.x,rockP.y,rock.w,rock.h}))
		   || (rectInRect( (ds_Rect){billP.x+/*head dist*/,billP.y,/*head w*/,/*head h*/},(ds_Rect){rockP.x,rockP.y,rock.w,rock.h}))){
			std::cout << "Score: " << score << std::endl << std::endl;
			std::cout << "Press A to play" << std::endl;
			dead = true;
			score = 0;
		
		}
			
		//}else if (rectInRect( (ds_Rect){billP.x+/*head dist*/,billP.y,/*head w*/,/*head h*/},(ds_Rect){rockP.x,rockP.y,rock.w,rock.h} )){
		/*if ( ((billP.x+bill.w) > rockP.x) && ((billP.x) < (rockP.x+rock.w)) ){
			//if bill in rock
			if ( ((billP.y+bill.h) > rockP.y) && ((billP.y) < (rockP.y+rock.h)) ){
				//std::cout << "in rock" << std::endl;
				std::cout << "Score: " << score << std::endl << std::endl;
				std::cout << "Press A to play" << std::endl;
				dead = true;
				score = 0;
			}else{
				//std::cout << "not" << std::endl;
			}
		}else{
			//if bill in rock
			if ( ((billP.y+bill.h) > rockP.y) && ((billP.y) < (rockP.y+rock.h)) ){
				//std::cout << "in rock" << std::endl;
				std::cout << "Score: " << score << std::endl << std::endl;
				std::cout << "Press A to play" << std::endl;
				dead = true;
				score = 0;
			}else{
				//std::cout << "not" << std::endl;
			}
		}*/

		rockP.x -= 4+score;

	}
	bgP.x-=5;
	if (bgP.x <= -400){
		bgP.x = 0;
	}
}

bool rectInRect(ds_Rect r1, ds_Rect r2){
	bool inside = false;
	if ( ((r1.x+r1.w) > r2.x) && ((r1.x) < (r2.x+r2.w)) ){
		//if bill in rock
		if ( ((r1.y+r1.h) > r2.y) && ((r1.y) < (r2.y+r2.h)) ){
			//std::cout << "in rock" << std::endl;
			inside = true;
		}
	}
	
	return inside;
}

void mainScreen::draw(ds_GFX gfx){
	gfx.beginFrame(GFX_TOP);
	gfx.clear((ds_Col){0,0,0});

	//for (int i = 0; i < 400*240*3; i+=3){
	//	std::cout << backImg.Buffer[i+2] << ',' << backImg.Buffer[i+1] << ',' << backImg.Buffer[i] << std::endl;
	//}
	gfx.drawImage(bgP,&backImg);
	gfx.drawImage((ds_Point){bgP.x+400,bgP.y},&backImg);
	gfx.drawImage(billP,&bill,(ds_Col){222,0,255});
	gfx.drawImage(rockP,&rock,(ds_Col){222,0,255});
}
