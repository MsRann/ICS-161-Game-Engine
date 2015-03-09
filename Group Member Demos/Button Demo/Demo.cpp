#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <res_path.h>
#include <cleanup.h>
#include <SDL_ttf.h>
#include "Button.h"
#include <functional>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 480;
//We'll just be using square tiles for now
const int TILE_SIZE = 40;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}


int main(int argc, char **argv){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Lesson 6", 100, 100, SCREEN_WIDTH,
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
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	const std::string resPath = getResourcePath("Button Demo") + "button.png";
	int x = 100, y = 100, w = 200, h = 100;
	std::function<void()> f = [&]() {x += 20; y += 20; };
	Button b(renderer, resPath, f);

	b.setDimension(x,y,w,h);

	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			b.handleEvents(&e);
		}
		//Render the scene
		SDL_RenderClear(renderer);
		b.setDimension(x, y, w, h);
		b.drawButton();
		SDL_RenderPresent(renderer);
	}



	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}