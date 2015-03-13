//#include <iostream>
//#include <sstream>
//#include <Windows.h>
//#include <SDL.h>
//#include "res_path.h"
//#include "cleanup.h"
//#include "SDL_image.h"
//#include "Sprite.h"
//
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
///**
//* Log an SDL error with some error message to the output stream of our choice
//* @param os The output stream to write the message to
//* @param msg The error message to write, format will be msg error: SDL_GetError()
//*/
//void logSDLError(std::ostream &os, const std::string &msg){
//	os << msg << " error: " << SDL_GetError() << std::endl;
//	std::ostringstream errMsg;
//	errMsg << " error: " << SDL_GetError() << std::endl;
//	OutputDebugString(errMsg.str().c_str());
//}
//
///**
//* Loads an image into a texture on the rendering device
//* @param file The image file to load
//* @param ren The renderer to load the texture onto
//* @return the loaded texture, or nullptr if something went wrong.
//*/
//SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
//	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
//	if (texture == nullptr){
//		logSDLError(std::cout, "LoadTexture");
//	}
//	return texture;
//}
//
//
//int main(int argc, char **argv){
//
//	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
//		std::ostringstream debugMsg;
//		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
//		OutputDebugString(debugMsg.str().c_str());
//		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
//		return 1;
//	}
//
//	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
//		logSDLError(std::cout, "IMG_Init");
//		SDL_Quit();
//		return 1;
//	}
//	
//	SDL_Window *window = SDL_CreateWindow("Sprite Demo", 800, 100, SCREEN_WIDTH,
//		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//	if (window == nullptr){
//		logSDLError(std::cout, "CreateWindow");
//		SDL_Quit();
//		return 1;
//	}
//	
//	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
//		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//	if (renderer == nullptr){
//		logSDLError(std::cout, "CreateRenderer");
//		cleanup(window);
//		SDL_Quit();
//		return 1;
//	}
//	
//	const std::string resPath = getResourcePath("SpriteDemo");
//	// background is from "iceland1.jpg" at theadventurousmailbox.com
//	SDL_Texture *background = loadTexture(resPath + "BowsersCastle.png", renderer);
//	//Make sure all is well
//	if (background == nullptr){
//		cleanup(background, renderer, window);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//	//SDL_Color transparent1 = { 255, 255, 255 };
//	Sprite* spriteBG = new Sprite(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
//	spriteBG->setPos(0, 0);
//	int bgFrame = spriteBG->makeFrame(background, 0, 0, 0.0);
//
//	SDL_Texture *spritesheet = loadTexture(resPath + "player.png", renderer);
//	// spritesheet is from "player.png" at www.briancollins1.com
//	if (spritesheet == nullptr){
//		cleanup(spritesheet, renderer, window);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//
//	SDL_Texture *spritesheet2 = loadTexture(resPath + "Up.png", renderer);
//	if (spritesheet2 == nullptr){
//		cleanup(spritesheet2, renderer, window);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//
//	SDL_Texture *spritesheet3 = loadTexture(resPath + "Down.png", renderer);
//	if (spritesheet3 == nullptr){
//		cleanup(spritesheet3, renderer, window);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//
//	std::string myPath = resPath + "Bowser.png";
//	SDL_Surface* spritesheetTest2 = IMG_Load(myPath.c_str());
//	//SDL_DisplayFormat(surface);
//	SDL_SetColorKey(spritesheetTest2, 1, SDL_MapRGB(spritesheetTest2->format, 255, 255, 255));
//	//SDL_SetColorKey(spritesheetTest, SDL_SRCCOLORKEY, transparent);
//
//	SDL_Texture *spritesheetTest = SDL_CreateTextureFromSurface(renderer, spritesheetTest2);
//	//SDL_Texture *spritesheetTest = loadTexture(resPath + "Bowser.png", renderer);
//	if (spritesheetTest == nullptr){
//		cleanup(spritesheetTest, renderer, window);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//	
//
//	
//	/*Sprite* sprite1 = new Sprite(95, 130, renderer);
//	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 0, 0));
//	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 95, 0));
//	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 190, 0));
//	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 285, 0));
//	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 380, 0));
//	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 475, 0));
//	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, 570, 0));
//
//	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet, 570, 260));
//	sprite1->addFrameToSequence("float up", sprite1->makeFrame(spritesheet2, 0, 0));
//	for (int i = 0; i<13; i++)
//	{
//		for (int j = 0; j<5; j++)
//		{
//			sprite1->addFrameToSequence("float down", sprite1->makeFrame(spritesheet3, 0, i * 130));
//		}
//	}*/
//	
//	Sprite* sprite2 = new Sprite(30, 45, renderer);//
//	
//	sprite2->addFrameToSequence("spin", sprite2->makeFrame(spritesheetTest, 1, 153, 0.1));//
//	sprite2->addFrameToSequence("spin", sprite2->makeFrame(spritesheetTest, 36, 153, 0.1));//
//	sprite2->addFrameToSequence("spin", sprite2->makeFrame(spritesheetTest, 69, 153, 0.1));
//	sprite2->addFrameToSequence("spin", sprite2->makeFrame(spritesheetTest, 104, 153, 0.1));
//	sprite2->addFrameToSequence("spin", sprite2->makeFrame(spritesheetTest, 136, 153, 0.1));//
//	sprite2->addFrameToSequence("spin", sprite2->makeFrame(spritesheetTest, 169, 153, 0.1));//
//	sprite2->addFrameToSequence("spin", sprite2->makeFrame(spritesheetTest, 201, 153, 0.1));//
//
//	///////////////////////////////////////////////////////////////////////////////////
//
//	///////////////////////////////////////////////////////////////////////////////////
//	sprite2->addFrameToSequence("Bowser walk up or down", sprite2->makeFrame(spritesheetTest, 5, 15, 0.3));//
//
//
//	///////////////////////////////////////////////////////////////////////////////////
//	sprite2->addFrameToSequence("Bowser walk up or down", sprite2->makeFrame(spritesheetTest, 49, 15, 0.3));//
//
//	///////////////////////////////////////////////////////////////////////////////////
//
//	///////////////////////////////////////////////////////////////////////////////////
//	sprite2->addFrameToSequence("Bowser walk left", sprite2->makeFrame(spritesheetTest, 2, 60, 0.3));//
//
//	///////////////////////////////////////////////////////////////////////////////////
//	sprite2->addFrameToSequence("Bowser walk left", sprite2->makeFrame(spritesheetTest, 48, 60, 0.3));//
//
//	///////////////////////////////////////////////////////////////////////////////////
//
//	int x = SCREEN_WIDTH / 2;
//	int y = SCREEN_HEIGHT / 2;
//	sprite2->setPos(x, y);//
//
//	SDL_Event e;
//	bool quit = false;
//	std::string spriteDirection = "spin";
//	while (!quit){
//		while (SDL_PollEvent(&e)){
//			if (e.type == SDL_QUIT){
//				quit = true;
//			}
//			if (e.type == SDL_KEYDOWN){
//				if (e.key.keysym.sym == SDLK_RIGHT)
//				{	
//					sprite2->movex(2);
//					spriteDirection = "spin";
//				}
//				else if (e.key.keysym.sym == SDLK_LEFT)
//				{
//					sprite2->movex(-1);
//					spriteDirection = "Bowser walk left";
//				}
//				else if (e.key.keysym.sym == SDLK_UP)
//				{
//					sprite2->movey(-1);
//					spriteDirection = "Bowser walk up or down";
//				}
//				else if (e.key.keysym.sym == SDLK_DOWN)
//				{
//					sprite2->movey(1);
//					spriteDirection = "Bowser walk up or down";
//				}
//			}
//		}
//		//Render the scene
//		SDL_RenderClear(renderer);
//		spriteBG->show(bgFrame);
//
//		
//		sprite2->show(spriteDirection.c_str());
//		SDL_RenderPresent(renderer);
//	}
//	cleanup(background, spritesheet, spritesheet2, spritesheet3,spritesheetTest, renderer, window);//
//	IMG_Quit();
//	SDL_Quit();
//
//	SDL_Quit();
//
//	return 0;
//}
