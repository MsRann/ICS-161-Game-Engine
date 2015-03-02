#pragma once

#include "SDL.h"
#include "GameObject.h"
#include <SDL_mixer.h>
#include <vector>
#include <map>


class Sprite : public GameObject
{
public:
	//By default borders are set to null
	Sprite(int x, int y, int width, int height, SDL_Renderer* ren);

	//new constructor that specifies a rectangle border that the sprite cannot get through
	//if the border is invalid it notifies the programmer that it didn't set one
	//if it is valid, the current x and y are set to be within the border and at the top left
	Sprite(int x, int y, int width, int height, SDL_Rect* border, SDL_Renderer* ren);
	
	~Sprite(void);

	// makeFrame returns the unique index of the frame
	int makeFrame(SDL_Texture* texture, int x, int y);

	// addFrameToSequence returns the number of frames in the sequence after the add
	int addFrameToSequence(std::string seqName, int frameIndex);

	// show(int) renders the frame with the specified frameIndex
	// also shows the border if it is toggled on and border is not null
	//void show(int frameIndex);

	// show(string) cycles through all frames in the specified sequence, one per call
	// also shows the border if it is toggled on and border is not null
	//void show(std::string sequence);

	void show();

	std::string getSequence();
	void setSequence(std::string newSequenceName);

    void render() override;

	void update() override;

// The private part of the class is given as a hint or suggestion.
// In homework 3 you can make any modifications you want to the class's innards.
private:
//	int width, height;
//	int currX, currY;		// the coordinates of the sprite's upper left hand corner relative to the window
//	SDL_Renderer* renderer;

	std::string currSequence;
	std::string last_seq;

	struct frame
	{
		SDL_Texture* texture;
		int x;
		int y;
	};
	std::vector<frame> frames;
	//string to hold name of last sequence called

	std::map<std::string, std::vector<int>> sequenceList;
	 
	int sequenceIndex;		// shared by all sequences; it would be better to have
							// one for each sequence
};