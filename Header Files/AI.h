#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include "Sprite.h"

class AI
{
public:
	AI(Sprite* entity, Sprite* entity2, int mode = 0);
	~AI(void);

	void move(Sprite* entity, Sprite* entity2);

	void move1(Sprite* entity, Sprite* entity2);

	void action();

private:
	Sprite* entity0, *entity1;
	int movex=1, movey, dx,dy, idle_total=0;
	double distance;
	int mode;
	int speed;
	SDL_Rect boundaries;
};
