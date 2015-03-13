#pragma once
#include "SDL.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class GameObject
{
public:
	GameObject::GameObject(string name, float xpos,float ypos,SDL_Renderer* ren );
	GameObject::GameObject(string name, float xpos, float ypos, float width, float height, SDL_Renderer* ren);
	GameObject::GameObject(string name, float xpos, float ypos, float width, float height, SDL_Rect* border, SDL_Renderer* ren);
	~GameObject(void);

	SDL_Renderer* getRenderer();

	string getName();

	float getX();
	float getY();

	void setX(float newX);
	void setY(float newY);

	float getWidth();
	void setWidth(float newWidth);

	float getHeight();
	void setHeight(float newHeight);
	
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
	void setPos(float x, float y);
	//doesn't allow movement past border in x if there is one
	void movex(float delta);
	//doesn't allow movement past border in y if there is one
	void movey(float delta);

	void move_normalized(float x, float y, float speed);
	
	struct updateToDo{
		std::string type;
		std::string change;
	};

	string name;

	std::vector<updateToDo> updates;
private:
	float x, y, width, height;
	bool collidable;
	SDL_Rect* border;
	bool displayBorder;
	SDL_Renderer* ren;
};