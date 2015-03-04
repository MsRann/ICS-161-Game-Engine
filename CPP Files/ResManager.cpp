#include "ResManager.h"
#include "res_path.h"
#include <iostream>

ResManager::ResManager(std::string path) {
	resPath = getResourcePath(path);
}

ResManager::~ResManager() {
	for (auto& x: textures) {
		SDL_DestroyTexture(getTexture(x.first));
	}
	textures.clear();
}

SDL_Texture* ResManager::getTexture(const std::string& textureID) { 
	return textures[textureID]; 
}

void ResManager::loadTexture(std::string textureID, std::string fileName, SDL_Renderer *ren) {
	textures[textureID] = IMG_LoadTexture(ren, (resPath + fileName).c_str());
	if (getTexture(textureID) == nullptr) {
		std::cout << fileName << " does not exist!" << std::endl;
		SDL_DestroyTexture(getTexture(textureID));
		textures.erase(textureID);
	}
}