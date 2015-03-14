// Texty.h

#pragma once

#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"

class Texty
{

public:
	Texty(SDL_Renderer* renderer, std::string fontName, int fontSize = 10, bool visible = true);

	// Added another contructor for users to be able to specify the color of the font
	Texty(SDL_Renderer* renderer, std::string fontName, int fontSize, bool visible, SDL_Color textColor);
	~Texty();

	enum writeOption_t {CONTINUE, NEXT_LINE};

	void write(std::string text, writeOption_t option = Texty::CONTINUE);

	void write(std::string text, int x, int y);

private:
	int nextX, nextY;
	int lineStartX;
	int fontSize;
	std::string fontName;
	std::string lastMessage;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* texture;
	SDL_Color color; 
	bool error;
	bool visible;

	void yikes(std::string message); // for error conditions
	SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
		SDL_Color color, int fontSize, SDL_Renderer *renderer);
};
