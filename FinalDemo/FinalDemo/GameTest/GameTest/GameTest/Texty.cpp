#include "texty.h"

/* HANDLING ERROR CONDITIONS
*
* The function yikes() is called when the following errors occur:
*
* (1) Error opening the font file
* (2) Error rendering the text onto the surface
* (3) Error creating the texture from the surface
*
* The yikes() function prints an error message to the screen.
*/

//void logSDLError(std::ostream &os, const std::string &msg);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

/**
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param fontSize The size we want the font to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*
* Code referenced from: http://www.willusher.io/sdl2%20tutorials/2013/12/18/lesson-6-true-type-fonts-with-sdl_ttf/
*/
SDL_Texture* Texty::renderText(const std::string &message, const std::string &fontFile,
	SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
	TTF_Init();

	//Open the font
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr){
		//yikes("TTF_OpenFont");
		return nullptr;
	}

	/* PART 2 - BETTER TEXTY - COLOR AWARE
	* I chose to implement the functionality of making Texty color aware
	* so that the text is always visible, no matter what color is used
	* for the font.
	*
	* Instead of using TTF_RenderText_Blended, I used TTF_RenderText_Shaded to
	* be able to apply a background color to the text. I also added another contructor
	* to allow users to be able to specify a color for the text class. The background
	* color of the text will either be white or black, according to the color of the text.
	*
	* If the RGB values add up to less than 575, then the background is white. Otherwise, the
	* background is black. The number 575 was chosen because I felt that colors over 575 were
	* too difficult to read against a white background, making black a more convenient choice.
	*
	* My original strategy to this problem was to make the background color of the text the inverse
	* of the text color, but this did not prove to always be legible (purple text with pink background).
	* This is why I chose to keep the background between two simple colors: black or white.
	*/

	/*SDL_Color bgColor;
	SDL_Color textColor = color;
	
	int r = textColor.r;
	int b = textColor.b;
	int g = textColor.g;
	int a = textColor.a;

	if (r + b + g > 575)
		bgColor = { 0, 0, 0, 0 };
	else
		bgColor = {255, 255, 255, 0};*/

	/*SDL_Surface *surf = TTF_RenderText_Shaded(font, message.c_str(), color, bgColor);
	if (surf == nullptr){
		TTF_CloseFont(font);
		//yikes("TTF_RenderText");
		return nullptr;
	}*/

	SDL_Surface *surf = TTF_RenderText_Solid(font, message.c_str(), color);
	if (surf == nullptr){
	TTF_CloseFont(font);
	//yikes("TTF_RenderText");
	return nullptr;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
		//yikes("CreateTexture");
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

void Texty::yikes(std::string message)
{
	//logSDLError(std::cout, message);
}

Texty::Texty(SDL_Renderer* renderer, std::string fontName, int fontSize, bool visible)
{
	this->fontSize = fontSize;
	this->fontName = fontName;
	this->renderer = renderer;

	color = { 0, 0, 0, 0 }; // Black by default
	bool error = false;
	this->visible = visible;
}

Texty::Texty(SDL_Renderer* renderer, std::string fontName, int fontSize, bool visible, SDL_Color textColor)
{
	this->fontSize = fontSize;
	this->fontName = fontName;
	this->renderer = renderer;

	color = textColor;
	bool error = false;
	this->visible = visible;
}

Texty::~Texty()
{
}

enum writeOption_t { CONTINUE, NEXT_LINE };

void Texty::write(std::string text, writeOption_t option)
{
	if (option == NEXT_LINE)
	{
		nextX = lineStartX;
		nextY += 15;
		if (!text.empty())
		{
			texture = renderText(text, fontName, color, fontSize, renderer);
			renderTexture(texture, renderer, nextX, nextY);
		}
	}
	else
	{
		int xOff =	lastMessage.length() * fontSize;
		nextX += 175;
		if (!text.empty())
		{
			texture = renderText(text, fontName, color, fontSize, renderer);
			renderTexture(texture, renderer, nextX, nextY);
		}
	}
}

void Texty::write(std::string text, int x, int y)
{
	nextX = x;
	nextY = y;
	lineStartX = x;

	texture = renderText(text, fontName, color, fontSize, renderer);
	renderTexture(texture, renderer, x, y);
	lastMessage = text;
}