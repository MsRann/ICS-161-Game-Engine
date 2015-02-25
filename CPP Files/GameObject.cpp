#include "GameObject.h"

GameObject::GameObject(int xpos,int ypos,SDL_Renderer* ren ):x(xpos), y(ypos), ren(ren){
	displayBorder = false;
	border = nullptr;
	width = 0; 
	height = 0;
}
GameObject::GameObject(int xpos,int ypos,int width, int height, SDL_Renderer* ren ):x(xpos), y(ypos), ren(ren),width(width),height(height){
	displayBorder = false;
	border = nullptr;
}


GameObject::GameObject(int xpos,int ypos,int width, int height,SDL_Rect* border, SDL_Renderer* ren): x(xpos), y(ypos), ren(ren),width(width),height(height),border(border){
	if (border != nullptr && (border->h < height || border->w < width)){
		this->border = nullptr;
		SDL_Log("Border not valid size. Border now set to null\n");
	}else{
		//place sprite in the same x and y in border
		if (border != nullptr){
			setX(border->x);
			setY(border->y);
		}
	}
	displayBorder = false;
}

GameObject::~GameObject(){
	delete border;
}

SDL_Renderer* GameObject::getRenderer(){
	return ren;
}

int GameObject::getX(){
	return x;
}

void GameObject::setX(int newX){
	x = newX;
}

int GameObject::getY(){
	return y;
}

void GameObject::setY(int newY){
	y =  newY;
}

int GameObject::getWidth(){
	return width;
}

void GameObject::setWidth(int newWidth){
	width = newWidth;
}

int GameObject::getHeight(){
	return height;
}

void GameObject::setHeight(int newHeight){
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

}


void GameObject::setPos(int x, int y){
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
void GameObject::movex(int delta){
	int temp = x + delta;

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
void GameObject::movey(int delta){
		
	int temp = y + delta;

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