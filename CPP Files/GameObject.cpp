#include "GameObject.h"

GameObject::~GameObject(void){
	if (mySprite != nullptr){
		delete mySprite;
	}
}

void GameObject::addSprite(Sprite* x){
	mySprite = x;
}

void GameObject::removeSprite(){
	if (mySprite != nullptr){
		delete mySprite;
		mySprite = nullptr;
	}
}

void GameObject::setCollidable(bool state){
	collidable = state;
}

Sprite* GameObject::getSprite(){
	return mySprite;
}

bool GameObject::getCollidable(){
	return collidable;
}

void GameObject::update(){

}

void GameObject::render(){
	if (mySprite != nullptr){
		mySprite->show(0);
	}
}
