#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include <SDL_image.h>
#include <string>
#include <functional>

class Button
{
public:
	//The image file should be an image of 3 buttons placed horizontally, with the leftmost button image being the default button image, the middle
	//one of the mouse hovering over the button, and the last one the image of the button when it is clicked. The function parameter is called when
	//the button is clicked.
	Button(SDL_Renderer* ren, std::string filepath, std::function<void ()>& func);

	//Call the setDimension function after creating a button to place the button's location and size on the renderer.
	void setDimension(int x, int y, int w, int h);
	//Call the handleEvents method in the event handling loop passing in the event.
	void handleEvents(SDL_Event* e);
	//Call the drawButton method in the rendering loop
	void drawButton();


private:
	std::function<void()> f;
	SDL_Renderer* ren;
	SDL_Texture* texture;
	SDL_Rect pos;
	SDL_Rect clip;
};

#endif