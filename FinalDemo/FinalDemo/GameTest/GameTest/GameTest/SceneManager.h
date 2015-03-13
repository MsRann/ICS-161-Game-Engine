#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

//#include "Scientist.h"
#include "GameObject.h"
#include "Background.h"
#include "Sprite.h"
#include "Scene.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>

class SceneManager{
public:
	//We can pass the renderer in only once here and save a lot of space in other objects.
	SceneManager(SDL_Renderer* renderer);
	~SceneManager(){}

	void addGameObjectToScene(std::string sceneName, GameObject* object);

	//Add Level 1
	void addSceneToSceneMap(std::string sceneName,Background* background);


	//Returns true if the action was completed
	bool changeScene(std::string sceneName);

	void renderAll(std::string sceneName, std::string sequence, bool moving);

	void updateAll(std::string sceneName);

private:
	SDL_Renderer* ren;

	//struct Scene
	//{
	//	//Pointer to the Background of the Scene
	//	Background* background;

	//	//Vector of Scientist objects
	//	std::vector < GameObject* > objects = std::vector < GameObject* >();
	//	//Scene(Background background):background(background){}
	//	//Scene(Background* background, std::vector < Scientist* > objects) : background(background), objects(objects){}
	//};

	//Map of each Scene Name and their Number representation in sceneList vector.
	std::map<std::string, Scene> SceneMap;


};

#endif //SCENEMANAGER_HPP