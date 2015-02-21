#pragma once
#include "Sprite.h"
#include "SDL.h"
#include <vector>
#include <map>

class GameObject
{
public:
	GameObject::GameObject(int xpos,int ypos):x(xpos), y(ypos){};
	~GameObject(void);

	void setSprite(Sprite* x);
	void removeSprite();
	Sprite* getSprite();

	void setCollidable(bool state);
	bool getCollidable();

	virtual void update();
	virtual void render();

private:
	int x, y;
	bool collidable;
	Sprite* mySprite;
	SDL_Renderer* ren;
};