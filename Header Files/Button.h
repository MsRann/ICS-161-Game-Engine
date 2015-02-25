#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include <SDL_image.h>
#include <vector>
#include <map>
#include "res_path.h"
#include <iostream>

using namespace std;

class Button
{
public:

	Button();

	void setButtonSize(int width, int height);
	void setButtonPosition(int x, int y);
	// Think about passing ints or an RGBA value, instead of passing SDL_Color (programmer shouldn't be worrying about SDL)
	void setButtonColor(SDL_Color &color);
	// Think about passing a string with the file name of the image, instead of passing SDL_Texture (again, programmer shouldn't be worrying about SDL)
	void setButtonImage(SDL_Texture &texture); 
	void drawButton();
	bool onClick();
	bool onHover();

	~Button();

private:

	int width;
	int height;
	int x;
	int y;
	SDL_Color &color;
	SDL_Texture &texture;
};

#endif

