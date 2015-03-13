#ifndef SCENE_HPP
#define SCENE_HPP

#include "Background.h"
#include "Scientist.h"
#include "GameObject.h"

class Scene{
public:

	//Pointer to the Background of the Scene
	Background* background;
	
	//Vector of game objects
	std::vector < GameObject* > objects = std::vector < GameObject* >();

	void Scene::applyCollisions(){
		for (int i = 0; i < this->objects.size(); i++){
			GameObject * obj1 = this->objects[i];
			for (int j = i + 1; j < this->objects.size(); j++){
				GameObject * obj2 = this->objects[j];
				float x = obj1->getX() - obj2->getX();
				float y = obj1->getY() - obj2->getY();
				float dist = (x * x) + (y * y);
				//if (dist < obj1->getRadius() + obj2->getRadius()){
				if (dist < obj1->getWidth()/2 + obj2->getWidth()/2){
					std::cout << obj1->name << " at " << obj1->getX() << " " << obj1->getY() << ";" << obj2->name << " at " << obj2->getX() << " " << obj2->getY() << " Collision at " << (obj1->getX() + obj2->getX()) / 2 << "," << (obj1->getY() + obj2->getY()) / 2 << std::endl;
				}
			}
		}
	}
};



#endif //SCENE_HPP