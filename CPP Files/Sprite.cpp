
#include "Sprite.h"
#include <string>

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param dst The destination rectangle to render the texture to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
	SDL_Rect *clip = nullptr)
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
	SDL_Rect *clip = nullptr)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr){
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture(tex, ren, dst, clip);
}


Sprite::Sprite(int x, int y, int width, int height, SDL_Renderer* ren) : GameObject(x,y,width,height,ren){
	currSequence = "default";
	
	sequenceIndex = 0;
	last_seq = "";
};

//throws an error when border is too small and set border to a nullptr
//sets the sprite position to the border position so it is not automatically out of the border
Sprite::Sprite(int x, int y, int width, int height,  SDL_Rect* border,SDL_Renderer* ren) 
	: GameObject(x,y,width,height,border,ren){
	currSequence = "default";
	sequenceIndex = 0;
	last_seq = "";

}; 

Sprite::~Sprite(){
}


// makeFrame returns the unique index of the frame
int Sprite::makeFrame(SDL_Texture* texture, int x, int y){
	frame newFrame = {texture,x,y};
	frames.push_back(newFrame);
	return frames.size()-1;
}

// addFrameToSequence returns the number of frames in the sequence after the add
int Sprite::addFrameToSequence(std::string seqName, int frameIndex){
	sequenceList[seqName].push_back(frameIndex);
	return sequenceList[seqName].size()-1;
}

std::string Sprite::getSequence(){
	return currSequence;
}

void Sprite::setSequence(std::string newSequence){
	//currSequence = newSequence;
	updateToDo newUpdate = {"changeSequence",newSequence};
	updates.push_back(newUpdate);
}


// show(string) cycles through all frames in the specified sequence, one per call

void Sprite::show(){
	//if it can't find the specified sequence
	if ( sequenceList.find(currSequence) == sequenceList.end()){
		SDL_Log("Couldn't find specified sequence name");
	}else{

		//reset sequence index if not the same frame sequence as previous
		if (last_seq != currSequence){
			last_seq = currSequence;
			sequenceIndex = 0;
		}
		SDL_Rect showFrame = {frames[sequenceList[currSequence].at(sequenceIndex)].x,frames[sequenceList[currSequence].at(sequenceIndex)].y,getWidth(),getHeight()};
		renderTexture(frames[sequenceList[currSequence].at(sequenceIndex)].texture,getRenderer(),getX(),getY(),&showFrame);
	
		if (getIfShowingBorder() && getBorder() != nullptr){
			SDL_RenderDrawRect(getRenderer(), getBorder());
		}
		sequenceIndex++;
		if (sequenceList[currSequence].size() == sequenceIndex){
			sequenceIndex = 0;
		}
	}
}

void Sprite::render() {
	show();
}

void Sprite::update(){
	for (int i = 0; i < updates.size(); i ++){
		if (updates[i].type == "y"){
			setY(std::stoi(updates[i].change));
		}else if (updates[i].type == "x"){
			setX(std::stoi(updates[i].change));
		}else if (updates[i].type == "changeSequence"){
			currSequence = updates[i].change;
		}
	}
	updates.clear();
}

void Sprite::addSound(std::string soundName, std::string fileName)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
	printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
	printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	Mix_Chunk *sound;

	sound = Mix_LoadWAV(fileName.c_str());

	if (sound == NULL)
	{
	printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	soundList[soundName] = sound;
}

void Sprite::playSound(std::string soundName)
{
	Mix_PlayChannel(-1, soundList[soundName], 0);
}
