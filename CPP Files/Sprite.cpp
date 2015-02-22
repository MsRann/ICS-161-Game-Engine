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

//throws an error when border is too small and set border to a nullptr
//sets the sprite position to the border position so it is not automatically out of the border
Sprite::Sprite(int width, int height, SDL_Renderer* ren, SDL_Rect* border) 
	: width(width), height(height), renderer(ren),border(border){
		this->border = border;
		if (this->border->h < height || this->border->w < width){
			this->border = nullptr;
			SDL_Log("Border not valid size. Border now set to null\n");
		}else{
			//place sprite in the same x and y in border
			currX = border->x;
			currY = border->y;
		}
		sequenceIndex = 0;
		last_seq = "";
		displayBorder = false;
}; 

Sprite::~Sprite(){

}


void Sprite::setPos(int x, int y){
	//within the border
	if (border == nullptr ||  (x >= border->x && x <= border->x + border->w - width &&
			y >= border->y && y <= border->y + border->h - height)){
		currX = x;
		currY = y;
	}else {
		SDL_Log("Cannot set position of the sprite there, it would be outside of the border. Ignoring setPos.\n");
	}
}

//Takes into account the width of the sprite and doesn't let the entire sprite out of the border
void Sprite::movex(int delta){
	currX += delta;
	if (border != nullptr){
		//dont let it get too far left
		if (currX < border->x){
			currX -= delta;

		//or too far right
		}else if (currX > (border->x + border->w - width)){
			currX -= delta;
		}
	}
}

//Takes into account the height of the sprite and doesn't let the entire sprite out of the border
void Sprite::movey(int delta){
	currY += delta;

	//check if a border is set
	if (border != nullptr){
		//dont let it get too far up
		if (currY < border->y){
			currY -= delta;

		//dont let it get too far down
		}else if (currY > (border->y + border->h - height)){
			currY -= delta;
		}
		
	}
	
}

int Sprite::getX(){
	return currX;
}

int Sprite::getY(){
	return currY;
}

int Sprite::getWidth(){
	return width;
}

int Sprite::getHeight(){
	return height;
}

void Sprite::setBorder(SDL_Rect* newBorder){
	if (currX >= newBorder->x && currX <= newBorder->x + newBorder->w - width &&
			currY >= newBorder->y && currY <= newBorder->y + newBorder->h - height){
		border = newBorder;
	}else{
		SDL_Log("Invalid border! Border not encompassing sprite, border was not set\n");
	}
}

SDL_Rect* Sprite::getBorder(){
	return border;
}

//returns previous border
SDL_Rect* Sprite::removeBorder(){
	SDL_Rect* temp = border;
	border = nullptr;
	return temp;
}

void Sprite::showBorder(bool option){
	displayBorder = option;
}

bool Sprite::getIfShowingBorder(){
	return displayBorder;
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

// show(int) renders the frame with the specified frameIndex
void Sprite::show(int frameIndex){
	SDL_Rect showFrame = {frames[frameIndex].x,frames[frameIndex].y,width,height};
	renderTexture(frames[frameIndex].texture,renderer,currX,currY,&showFrame);
	if (displayBorder && border != nullptr){
		SDL_RenderDrawRect(renderer, border);
	}
}

// show(string) cycles through all frames in the specified sequence, one per call
void Sprite::show(std::string sequence){
	//reset sequence index if not the same frame sequence as previous
	if (last_seq != sequence){
		last_seq = sequence;
		sequenceIndex = 0;
	}
	SDL_Rect showFrame = {frames[sequenceList[sequence].at(sequenceIndex)].x,frames[sequenceList[sequence].at(sequenceIndex)].y,width,height};
	renderTexture(frames[sequenceList[sequence].at(sequenceIndex)].texture,renderer,currX,currY,&showFrame);
	if (displayBorder && border != nullptr){
		SDL_RenderDrawRect(renderer, border);
	}
	sequenceIndex++;
	if (sequenceList[sequence].size() == sequenceIndex){
		sequenceIndex = 0;
	}
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
