//#ifndef SCIENTIST_HPP
//#define SCIENTIST_HPP
//#include "SDL.h"
//#include "Sprite.h"
//
//#include <string>
//#include <iostream>
//#include <sstream>
//
////To Do List:
////	Will need normalization for diagonal movement... This can be inherited from the GameObject class
////	Collision Detection
//
////Side Note:
////	The vertical and horizontal sprite walks have a 2 pixel size difference.
//
//
//
//class Scientist{
//public:
//	//Scientist(){}
//	Scientist(SDL_Texture* spritesheet,SDL_Renderer* ren, int startX, int startY, bool NPC = false);
//	~Scientist();
//
//	void moveScientist(std::string sequence);//, bool moving);
//	void renderScientist(std::string sequence , bool moving = false);
//	
//
//private:
//
//	std::string previousSequence;
//
//	Sprite* verticalSprite;
//	int verticalWidth = 14;
//	int verticalHeight = 20;
//
//	bool NPC;
//
//
//	//This implementation was kept in case there were multiple sprites for an object
//	//Sprite* horizontalSprite;
//	//int horizontalWidth = 12;
//	//int horizontalHeight = 20;
//
//	const std::string resPath;
//	SDL_Renderer* renderer;
//
//};
//
//
//
//#endif //SCIENTIST_HPP