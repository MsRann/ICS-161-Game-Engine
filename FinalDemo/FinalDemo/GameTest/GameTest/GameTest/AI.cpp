#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include "Sprite.h"
#include "AI.h"
#include <iostream>

//basic ai, simply strafes left and right, then chases specified entity2 that gets within range. Speed and range hardcoded to 1 and 150, but can be changed.
//AI takes 2 entities, which will be the GameObjects, entity1 is the entity inheriting the AI, entity2 is the player, mode is defaulted to idle(0), but can be chase(1).
//asked TA, says most AI classes don't inherit from gameobjects, so...made it this way?

AI::AI(Sprite* entity, Sprite* entity2, int mode){
	entity0 = entity;
	entity1 = entity2;
	mode = mode;
}

AI::~AI(void){}



void AI::move(Sprite* entity, Sprite* entity2){
	dx = entity2->getX()- entity->getX();
	dy = entity2->getY()-entity->getY();
	speed = 1;
	if (dx > 0)
		movex = speed;
	else
		movex = -speed;
	if (dy > 0)
		movey = speed;
	else
		movey = -speed;
	entity->movex(movex);
	entity->movey(movey);
	distance = sqrt((dx*dx) + (dy*dy));
	if (distance > 100){
		mode = 0;
	}
}

void AI::move1(Sprite* entity, Sprite* entity2){
	dx = entity2->getX() - entity->getX();
	dy = entity2->getY() - entity->getY();
	entity->movex(movex);
	idle_total += movex;
	if (abs(idle_total) > 35){
		movex = -movex;
		if (idle_total > 35)
			idle_total = 34;
		else if (idle_total < -35)
			idle_total = -34;
	}
	distance = sqrt((dx*dx) + (dy*dy));
	if (distance < 150){
		mode = 1;
	}
	
}


void AI::action(){
	if (mode == 1){
		move(entity0, entity1);
	}
	else if (mode == 0){
		move1(entity0,entity1);
	}
}
