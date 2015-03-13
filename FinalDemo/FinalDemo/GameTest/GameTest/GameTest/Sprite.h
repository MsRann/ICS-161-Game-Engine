#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SDL.h"
#include "GameObject.h"
#include <SDL_mixer.h>
#include <vector>
#include <map>

//Jake's includes
#include <chrono> //include chorno? OH NOOO!



class Sprite : public GameObject
{
public:
	//By default borders are set to null
	Sprite(std::string name,float x, float y, float width, float height, SDL_Renderer* ren);

	//new constructor that specifies a rectangle border that the sprite cannot get through
	//if the border is invalid it notifies the programmer that it didn't set one
	//if it is valid, the current x and y are set to be within the border and at the top left
	Sprite(std::string name, float x, float y, float width, float height, SDL_Rect* border, SDL_Renderer* ren);
	
	~Sprite(void);

	// makeFrame returns the unique index of the frame
	// Added the frameDuration parameter - Jake
	int makeFrame(SDL_Texture* texture, int x, int y,double frameTimeLength);

	// addFrameToSequence returns the number of frames in the sequence after the add
	int addFrameToSequence(std::string seqName, int frameIndex);

	//used in render
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
		double timeLength; // - Jake
	};
	std::vector<frame> frames;
	//string to hold name of last sequence called

	std::map<std::string, std::vector<int>> sequenceList;
	 
	int sequenceIndex;		// shared by all sequences; it would be better to have
							// one for each sequence
	// Variables for frame duration implementation - Jake
	std::chrono::high_resolution_clock::time_point timePrev; //To record the time since last update
	std::string prevSequence; //To reset the clock in changed sequences
	double GetTimeDifference(); //To calculate time difference since last frame update.


};
#endif //SPRITE_HPP