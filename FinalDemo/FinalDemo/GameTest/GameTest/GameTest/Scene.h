#ifndef SCENE_HPP
#define SCENE_HPP

#include "Background.h"
#include "Scientist.h"

class Scene{
public:

	//Pointer to the Background of the Scene
	Background* background;

	
	//Vector of game objects
	std::vector < GameObject* > objects = std::vector < GameObject* >();
};



#endif //SCENE_HPP