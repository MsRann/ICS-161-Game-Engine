#include "SceneManager.h"

SceneManager::SceneManager(SDL_Renderer* renderer){
	ren = renderer;
}
//SceneManager::~SceneManager(){}

void SceneManager::addSceneToSceneMap(std::string sceneName, Background* background){
	Scene toAdd;
	toAdd.background = background;
	//toAdd.objects;
	//SceneMap.insert(std::pair<std::string, Scene>(sceneName, toAdd));
	SceneMap[sceneName] = toAdd;
}

void SceneManager::addGameObjectToScene(std::string sceneName, GameObject* object){
	SceneMap[sceneName].objects.push_back(object);
	std::cout << SceneMap[sceneName].objects.size() << std::endl;
}

bool SceneManager::changeScene(std::string sceneName){
	return false;
}

void SceneManager::updateAll(std::string sceneName){
	for (int i = 0; i < SceneMap[sceneName].objects.size(); i++){
		SceneMap[sceneName].objects[i]->update();
	}
}



void SceneManager::renderAll(std::string sceneName, std::string sequence, bool moving){
	SceneMap[sceneName].background->renderBackground();
	//for (Scientist scientistInScene : SceneMap[sceneName].objects){
	//	scientistInScene.renderScientist(sequence, moving);
	//}
	for (int i = 0; i < SceneMap[sceneName].objects.size(); i++){
		//SceneMap[sceneName].objects[i]->renderScientist(sequence, moving);
		SceneMap[sceneName].objects[i]->render();
	}
	//SceneMap[sceneName].objects.at(0)->renderScientist(sequence, moving);
	//SceneMap[sceneName].objects.at(1)->renderScientist(sequence, moving);
	//SceneMap[sceneName].objects[0].renderScientist(sequence);
	
}