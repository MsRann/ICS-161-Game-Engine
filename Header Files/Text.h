#ifndef TEXT_H
#define TEXT_H

#include "SDL.h"
#include <SDL_image.h>
#include <vector>
#include <map>
#include "res_path.h"
#include <iostream>

using namespace std;

class Text
{
public:

	Text();

	void setFontStyle(string filename);
	void setFontSize(int size);
	void setFontColor(int r, int g, int b, int a); //Pass RBGA values for color
	void setTextMessage(string message);
	void setTextPosition(int x, int y);
	void drawMessage();
	void setTextBoundary();

	~Text();

private:

	int size;
	int x;
	int y;
	SDL_Color &color;
};

#endif

