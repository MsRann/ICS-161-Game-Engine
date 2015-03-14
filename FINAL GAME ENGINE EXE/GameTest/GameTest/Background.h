#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP


#include "SDL.h"

#include <string>
#include <iostream>
#include <sstream>


//To Do List
//	Need to add a boundary feature for the GameObjects inside

class Background{
public:
	//Appends the fileName to the resPath
	Background(){}
	Background(std::string fileName, int screenHeight, int screenWidth, SDL_Renderer* ren);

	//Clean up
	~Background();

	void changeBackground(std::string fileName);

	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
	void logSDLError(std::ostream &os, const std::string &msg);
	void renderBackground();

	//Need to add a border!!


	//int getWidth();
	//int getHeight();
	

private:
	const std::string resPath;

	SDL_Texture *background;// = loadTexture(resPath + fileName, renderer); //Do this in the constructor! Make sure it is found.
	SDL_Renderer* renderer;

	int ScreenHeight;
	int ScreenWidth;

	bool isNULL;
};


#endif //BACKGROUND_HPP