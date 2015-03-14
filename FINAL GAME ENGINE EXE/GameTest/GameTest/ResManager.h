#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <unordered_map>

class ResManager {

public:
	ResManager(std::string path);
	~ResManager();

	void loadTexture(std::string textureID, std::string fileName, SDL_Renderer *ren);

	SDL_Texture* getTexture(const std::string& textureID);
	//SDL_Texture& getFont(const std::string& fontID) { return *font[fontID]; }
	//SDL_Texture& getSound(const std::string& soundID) { return *sound[soundID]; }

private:

	std::string resPath;

	std::unordered_map<std::string, SDL_Texture*> textures;

};