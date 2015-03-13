#include "GameObject.h"
#include "string"
#include <iostream>
using namespace std;

GameObject::GameObject(string name, float xpos, float ypos, SDL_Renderer* ren) :name(name), x(xpos), y(ypos), ren(ren){
	displayBorder = false;
	border = nullptr;
	width = 0; 
	height = 0;
}
GameObject::GameObject(string name, float xpos, float ypos, float width, float height, SDL_Renderer* ren) :name(name), x(xpos), y(ypos), ren(ren), width(width), height(height){
	displayBorder = false;
	border = nullptr;
}


GameObject::GameObject(string name, float xpos, float ypos, float width, float height, SDL_Rect* border, SDL_Renderer* ren) :name(name), x(xpos), y(ypos), ren(ren), width(width), height(height), border(border){
	if (border != nullptr && (border->h < height || border->w < width)){
		this->border = nullptr;
		SDL_Log("Border not valid size. Border now set to null\n");
	}else{
		//place sprite in the same x and y in border
		if (border != nullptr){
			std::cout << "no" << std::endl;
			setX(border->x);
			setY(border->y);
		}
	}
	displayBorder = false;
}

GameObject::~GameObject(){
	//delete border;
}

SDL_Renderer* GameObject::getRenderer(){
	return ren;
}

string GameObject::getName(){
	return name;
}

float GameObject::getX(){
	return x;
}

void GameObject::setX(float newX){
	x = newX;
}

float GameObject::getY(){
	return y;
}

void GameObject::setY(float newY){
	y =  newY;
}

float GameObject::getWidth(){
	return width;
}

void GameObject::setWidth(float newWidth){
	width = newWidth;
}

float GameObject::getHeight(){
	return height;
}

void GameObject::setHeight(float newHeight){
	height = newHeight;
}

void GameObject::setCollidable(bool state){
	collidable = state;
}

bool GameObject::getCollidable(){
	return collidable;
}

void GameObject::update(){
	for (int i = 0; i < updates.size(); i ++){
		if (updates[i].type == "y"){
			setY(std::stoi(updates[i].change));
		}else if (updates[i].type == "x"){
			setX(std::stoi(updates[i].change));
		}
	}
	updates.clear();
}

void GameObject::render(){
	if (getIfShowingBorder() && getBorder() != nullptr){
		SDL_RenderDrawRect(getRenderer(), getBorder());
	}
}


void GameObject::setPos(float x, float y){
	//within the border
	if (border == nullptr ||  (x >= border->x && x <= border->x + border->w - getWidth() &&
			y >= border->y && y <= border->y + border->h - getHeight())){
		setX(x);
		setY(y);
	}else {
		SDL_Log("Cannot set position of the sprite there, it would be outside of the border. Ignoring setPos.\n");
	}
}

//Takes into account the width of the sprite and doesn't let the entire sprite out of the border
void GameObject::movex(float delta){
	float temp = x + delta;

	//check if a border is set
	if (border != nullptr){
		//dont let it get too far up
		if (temp < border->x || temp > (border->x + border->w - getWidth()) ){
			temp = x;
		}
	}
	updateToDo newUpdate = {"x",std::to_string(temp)};
	updates.push_back(newUpdate);
}

//Takes into account the height of the sprite and doesn't let the entire sprite out of the border
void GameObject::movey(float delta){
		
	float temp = y + delta;

	//check if a border is set
	if (border != nullptr){
		//dont let it get too far up
		if (temp < border->y || temp > (border->y + border->h - getHeight())){
			temp = y;
		}
	}
	updateToDo newUpdate = {"y",std::to_string(temp)};
	updates.push_back(newUpdate);
}

void GameObject::move_normalized(float x, float y, float speed){
	if (x != 0 && y != 0){
		float len = speed / sqrt(x*x + y*y);
		x *= len;
		y *= len;
	}
	movex(x);
	movey(y);
}

void GameObject::setBorder(SDL_Rect* newBorder){
	if (x >= newBorder->x && x <= newBorder->x + newBorder->w - getWidth() &&
			y >= newBorder->y && y <= newBorder->y + newBorder->h - getHeight()){
		border = newBorder;
	}else{
		SDL_Log("Invalid border! Border not encompassing sprite, border was not set\n");
	}
}

SDL_Rect* GameObject::getBorder(){
	return border;
}

//returns previous border
SDL_Rect* GameObject::removeBorder(){
	SDL_Rect* temp = border;
	border = nullptr;
	return temp;
}

void GameObject::showBorder(bool option){
	displayBorder = option;
}

bool GameObject::getIfShowingBorder(){
	return displayBorder;
}
