#include "Background.h"
#include <Windows.h>
//#include "res_path.h"
#include "SDL_image.h"


Background::Background(std::string filePath, int screenWidth, int screenHeight, SDL_Renderer* ren)
	:resPath(filePath), renderer(ren), ScreenWidth(screenWidth), ScreenHeight(screenHeight){

	

	//Loading Background Image and setting isNULL to true if the operation failed.
	background = loadTexture(filePath, renderer);
	isNULL = background == nullptr;
}

Background::~Background(){}

void Background::changeBackground(std::string filePath){
	//Delete the old background?


	//Loading new background image and setting isNULL to true if the operation failed.
	background = loadTexture(filePath, renderer);
	isNULL = background == nullptr;
}

void Background::logSDLError(std::ostream &os, const std::string &msg){
	//Random error message stuff that I copy and pasted
	os << msg << " error: " << SDL_GetError() << std::endl;
	std::ostringstream errMsg;
	errMsg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());
}

SDL_Texture* Background::loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}


void Background::renderBackground(){
	//Setup the destination rectangle to be at the position we want
	//Should stretch to fit the window screen???????!!????
	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(background, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, background, NULL, NULL);// &dst);

}
