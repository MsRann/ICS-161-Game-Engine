//Press d in order to toggle between displaying the border and not
//Press b in order to create a border at 320,240 with a width of 100 and height of 100

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include <vector>
#include "res_path.h"
#include "SDL_image.h"
#include "Sprite.h"
#include "GameObject.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
	std::ostringstream errMsg;
	errMsg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}


int main(int argc, char **argv){

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::ostringstream debugMsg;
		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
		OutputDebugString(debugMsg.str().c_str());
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Sprite Demo", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	const std::string resPath = getResourcePath("SpriteDemo");
	// background is from "iceland1.jpg" at theadventurousmailbox.com
	SDL_Texture *background = loadTexture(resPath + "Background.png", renderer);
	//Make sure all is well
	if (background == nullptr){

//		cleanup(background, renderer, window);
		SDL_DestroyTexture(background);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	Sprite* spriteBG = new Sprite(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
	int bgFrame = spriteBG->addFrameToSequence("default", spriteBG->makeFrame(background, 0, 0,0.0));
	spriteBG->setSequence("default");

	SDL_Texture *spritesheet = loadTexture(resPath + "LoZRight.png", renderer);
	// spritesheet is from "player.png" at www.briancollins1.com
	if (spritesheet == nullptr){
		SDL_DestroyTexture(spritesheet);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture *spritesheet2 = loadTexture(resPath + "LoZUp.png", renderer);
	if (spritesheet2 == nullptr){
		SDL_DestroyTexture(spritesheet2);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture *spritesheet3 = loadTexture(resPath + "LoZDown.png", renderer);
	if (spritesheet3 == nullptr){
		SDL_DestroyTexture(spritesheet3);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		//cleanup(spritesheet3, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

		SDL_Texture *spritesheet4 = loadTexture(resPath + "LoZLeft.png", renderer);
	if (spritesheet2 == nullptr){
		SDL_DestroyTexture(spritesheet2);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	//uncomment this code to see what will happen if an invalid border is set (border smaller than width and height of sprite
	//SDL_Rect tempRect =  {5,20,22,23};
	//Sprite* sprite1 = new Sprite(23, 26, renderer, &tempRect);
	int x = SCREEN_WIDTH / 2 ;
	int y = SCREEN_HEIGHT / 2;

	Sprite* sprite1 = new Sprite(x,y,23, 26, renderer);
	for (int i = 0; i < 6; i ++){
		sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 30*i, 0,0.3));
	}

	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet4, 0, 0,0.3));
	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet4, 24, 0,0.3));
	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet4, 49, 0,0.3));
	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet4, 72, 0,0.3));
	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet4, 98, 0,0.3));
	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet4, 145, 0,0.3));

	for (int i = 0; i < 6; i ++){
		sprite1->addFrameToSequence("float up", sprite1->makeFrame(spritesheet2, 30*i, 0,0.3));
	}

	for (int i = 0; i < 6; i ++){
		sprite1->addFrameToSequence("float down", sprite1->makeFrame(spritesheet3, 30*i, 0,0.3));
	}
	std::vector<GameObject*> gameObjects;
	gameObjects.push_back(spriteBG);
	gameObjects.push_back(sprite1);
	

	SDL_Event e;
	bool quit = false;
	sprite1->setSequence("float up");
	sprite1->update();

	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
			
				if (e.key.keysym.sym == SDLK_RIGHT)
				{
					sprite1->movex(1);
					sprite1->setSequence("walk right");
				}
				else if (e.key.keysym.sym == SDLK_LEFT)
				{
					sprite1->movex(-1);
					sprite1->setSequence("walk left");
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{
					sprite1->movey(-1);
					sprite1->setSequence("float up");
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					sprite1->movey(1);
					sprite1->setSequence("float down");
				}else if (e.key.keysym.sym == SDLK_b){
					if (sprite1->getBorder()== nullptr){
						printf("Set border\n");
						SDL_Rect temp = {x,y, 100,100};
						sprite1->setBorder(&temp);
					}else{
						printf("Removed Border\n");
						sprite1->removeBorder();
					
					}
				}else if (e.key.keysym.sym == SDLK_d){
					sprite1->showBorder(!sprite1->getIfShowingBorder());	
				
				}

			}
		}
		//Render the scene
		SDL_RenderClear(renderer);
		//changes position of sprites, what sequence its showing, etc
		for(int i=0; i < gameObjects.size(); i++){
			gameObjects[i]->update();
		}

		//displays GameObject on the screen
		for(int i=0; i < gameObjects.size(); i++){
			gameObjects[i]->render();
		}

		SDL_RenderPresent(renderer);
	}

	for(int i=0; i < gameObjects.size(); i++){
		delete gameObjects[i];
	}

	SDL_DestroyTexture(spritesheet4);		
	SDL_DestroyTexture(spritesheet3);
	SDL_DestroyTexture(spritesheet2);
	SDL_DestroyTexture(spritesheet);
	SDL_DestroyTexture(background);	

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}