#pragma once

#include "SDL.h"
#include <vector>
#include <map>

class Sprite
{
public:
	//By default borders are set to null
	Sprite(int width, int height, SDL_Renderer* ren) : width(width), height(height), renderer(ren){displayBorder = false;sequenceIndex = 0;last_seq = "";border=nullptr;};
	~Sprite(void);

	//new constructor that specifies a rectangle border that the sprite cannot get through
	//if the border is invalid it notifies the programmer that it didn't set one
	//if it is valid, the current x and y are set to be within the border and at the top left
	Sprite(int width, int height, SDL_Renderer* ren, SDL_Rect* border);

	//new helper methods that allow dynamic changes to the sprite border in game
	void setBorder(SDL_Rect* newBorder);
	SDL_Rect* getBorder();
	//returns the rectangle of the previous border if there was one, nullptr otherwise
	SDL_Rect* removeBorder();
	//display the rectangle on screen for debugging
	//if option is true then it displays it, toggles it off if not.
	void showBorder(bool option);
	//returns the state of whether the border is being displayed or not
	bool getIfShowingBorder();

	//not allowed to be set beyond border if there is one
	void setPos(int x, int y);
	//doesn't allow movement past border in x if there is one
	void movex(int delta);
	//doesn't allow movement past border in y if there is one
	void movey(int delta);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	// makeFrame returns the unique index of the frame
	int makeFrame(SDL_Texture* texture, int x, int y);

	// addFrameToSequence returns the number of frames in the sequence after the add
	int addFrameToSequence(std::string seqName, int frameIndex);

	// show(int) renders the frame with the specified frameIndex
	// also shows the border if it is toggled on and border is not null
	void show(int frameIndex);

	// show(string) cycles through all frames in the specified sequence, one per call
	// also shows the border if it is toggled on and border is not null
	void show(std::string sequence);

// The private part of the class is given as a hint or suggestion.
// In homework 3 you can make any modifications you want to the class's innards.
private:
	int width, height;
	int currX, currY;		// the coordinates of the sprite's upper left hand corner relative to the window
	SDL_Renderer* renderer;
	SDL_Rect* border;
	bool displayBorder;


	struct frame
	{
		SDL_Texture* texture;
		int x;
		int y;
	};
	std::vector<frame> frames;
	//string to hold name of last sequence called
	std::string last_seq;
	std::map<std::string, std::vector<int>> sequenceList;
	int sequenceIndex;		// shared by all sequences; it would be better to have
							// one for each sequence


};

