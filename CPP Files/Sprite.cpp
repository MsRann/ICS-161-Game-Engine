
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

double Sprite::GetTimeDifference(){
	// Get current time as a std::chrono::time_point
	// which basically contains info about the current point in time
	auto timeCurrent = std::chrono::high_resolution_clock::now();

	// Compare the two to create time_point containing delta time in nanosecnds
	auto timeDiff = std::chrono::duration_cast<std::chrono::nanoseconds>(timeCurrent - timePrev);

	// Get the tics as a variable
	double delta = timeDiff.count();

	// Turn nanoseconds into seconds
	delta /= 1000000000;

	//timePrev = timeCurrent;
	return delta;
}
// makeFrame returns the unique index of the frame
int Sprite::makeFrame(SDL_Texture* texture, int x, int y,double frameTimeLength){
	frame newFrame = {texture,x,y,frameTimeLength};
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



		if (currSequence != prevSequence){
			timePrev = std::chrono::high_resolution_clock::now();
		}
		prevSequence = currSequence;
	
		if (frames[sequenceList.at(currSequence)[sequenceIndex]].timeLength != 0.0){

			double diff = GetTimeDifference();
			//std::cout << diff << std::endl;

			//If the timeLength == 0.0 then it is never supposed to change
			//If the timer for the frame has been reached, advance to the next frame in the sequence
			//	If reached just passed the end of the sequence, set the sequence index back to 0
			if (diff >= frames[sequenceList.at(currSequence)[sequenceIndex]].timeLength){
			
				sequenceIndex++;
				if (sequenceIndex >= sequenceList.at(currSequence).size()){
					sequenceIndex = 0;
				}
				timePrev = std::chrono::high_resolution_clock::now();
			}
			if (sequenceIndex >= sequenceList.at(currSequence).size()){
				sequenceIndex = 0;
			}
		}

		SDL_Rect showFrame = {frames[sequenceList[currSequence].at(sequenceIndex)].x,frames[sequenceList[currSequence].at(sequenceIndex)].y,getWidth(),getHeight()};
		renderTexture(frames[sequenceList[currSequence].at(sequenceIndex)].texture,getRenderer(),getX(),getY(),&showFrame);
	

		if (getIfShowingBorder() && getBorder() != nullptr){
			SDL_RenderDrawRect(getRenderer(), getBorder());
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
