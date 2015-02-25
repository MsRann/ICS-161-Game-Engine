#pragma once
#include "SDL.h"
#include <string>
#include <vector>
#include <map>

class GameObject
{
public:
	GameObject::GameObject(int xpos,int ypos,SDL_Renderer* ren );
	GameObject::GameObject(int xpos,int ypos,int width, int height, SDL_Renderer* ren);
	GameObject::GameObject(int xpos,int ypos,int width, int height,SDL_Rect* border, SDL_Renderer* ren);
	~GameObject(void);

	SDL_Renderer* getRenderer();

	int getX();
	int getY();

	void setX(int newX);
	void setY(int newY);

	int getWidth();
	void setWidth(int newWidth);

	int getHeight();
	void setHeight(int newHeight);
	
	void setCollidable(bool state);
	bool getCollidable();

	virtual void update();
	virtual void render();


	//new helper methods that allow dynamic changes to the sprite border in game
	void setBorder(SDL_Rect* newBorder);
	SDL_Rect* getBorder();
	//returns the rectangle of the previous border if there was one, nullptr otherwise
	SDL_Rect* removeBorder();
	//display the rectangle on screen for debugging
	//if option is true then it displays it, toggles it off if not.
	void showBorder(bool option);
	//returns the state of whether the border is being displayed or not
	bool getIfShowingBorder();

	//not allowed to be set beyond border if there is one
	void setPos(int x, int y);
	//doesn't allow movement past border in x if there is one
	void movex(int delta);
	//doesn't allow movement past border in y if there is one
	void movey(int delta);
	
	struct updateToDo{
		std::string type;
		std::string change;
	};
	std::vector<updateToDo> updates;
private:
	int x, y,width,height;
	bool collidable;
	SDL_Rect* border;
	bool displayBorder;
	SDL_Renderer* ren;
};