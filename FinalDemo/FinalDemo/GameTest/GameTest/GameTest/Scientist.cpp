//#include "Scientist.h"
////#include "Sprite.h"
//
//
//Scientist::Scientist(SDL_Texture* spritesheet, SDL_Renderer* ren, int startX, int startY, bool NPC)
//	:renderer(ren), NPC(NPC){
//	//The reason for having verticalSprites and horizontalSprite is because the sprite size walking up/down is
//	//	a few pixels different from the sprite walking left/right.
//	//	I commented this out in case we needed it.
//	verticalSprite = new Sprite(verticalWidth, verticalHeight, renderer);
//	//horizontalSprite = new Sprite(horizontalWidth, horizontalHeight, renderer);
//
//	for (int i = 0; i < 3; i++){
//		verticalSprite->addFrameToSequence("walk down", verticalSprite->makeFrame(spritesheet, 18, 389 + (i * 30), 0.3));
//		verticalSprite->addFrameToSequence("walk up", verticalSprite->makeFrame(spritesheet, 78, 389 + (i * 30), 0.3));
//		verticalSprite->addFrameToSequence("walk right", verticalSprite->makeFrame(spritesheet, 109, 389 + (i * 30), 0.3));
//		verticalSprite->addFrameToSequence("walk left", verticalSprite->makeFrame(spritesheet, 49, 389 + (i * 30), 0.3));
//
//		//horizontalSprite->addFrameToSequence("walk right", horizontalSprite->makeFrame(spritesheet, 109, 389 + (i * 30), 0.5));
//		//horizontalSprite->addFrameToSequence("walk left", horizontalSprite->makeFrame(spritesheet, 49, 389 + (i * 30), 0.5));
//	}
//
//	//verticalSprite->addFrameToSequence("idle down", verticalSprite->makeFrame(spritesheet, 18, 389, 0.0));
//	//verticalSprite->addFrameToSequence("idle up", verticalSprite->makeFrame(spritesheet, 78, 389, 0.0));
//	//verticalSprite->addFrameToSequence("idle right", verticalSprite->makeFrame(spritesheet, 109, 389, 0.0));
//	//verticalSprite->addFrameToSequence("idle left", verticalSprite->makeFrame(spritesheet, 49, 389, 0.0));
//
//
//
//	verticalSprite->setPos(startX, startY);
//	//horizontalSprite->setPos(startX, startY);
//
//}
//
//Scientist::~Scientist(){
//	delete verticalSprite;
//	//delete horizontalSprite;
//}
//void Scientist::moveScientist(std::string sequence){// , bool moving){
//	//This is hard coded in.  Will need normalization for diagonal movement
//	int velocity = 1;
//	//if (sequence != previousSequence){
//	//	velocity = 1; //Initial speed when changing direction is a little slow.
//	//}
//	//else{
//	//	velocity = 2;
//	//}
//	if (sequence == "walk down"){
//		//if (moving == true){
//		//	verticalSprite->movey(velocity);
//		//}
//		verticalSprite->movey(velocity);
//	}
//	else if (sequence == "walk up"){
//		verticalSprite->movey(-velocity);
//	}
//	else if (sequence == "walk right"){
//		verticalSprite->movex(velocity);
//	}
//	else if (sequence == "walk left"){
//		verticalSprite->movex(-velocity);
//	}
//	
//
//}
//
//void Scientist::renderScientist(std::string sequence, bool moving){
//	//if ((sequence == "walk up") | (sequence == "walk down")){
//	//	verticalSprite->show(sequence);
//	//}
//	//else if ((sequence == "walk left") | (sequence == "walk right")){
//	//	horizontalSprite->show(sequence);
//	//}
//	if (NPC == true){
//		moveScientist("idle");
//		//verticalSprite->show("walk down");
//
//		//previousSequence = "walk down";
//	}
//	else if (moving == true){
//		moveScientist(sequence);//, moving);
//		//verticalSprite->show(sequence);
//		//previousSequence = sequence;
//	}
//	verticalSprite->show(sequence);
//
//	previousSequence = sequence;
//	//else{
//	//	std::string idleSequence = sequence.replace(0, 4, "idle");
//	//	verticalSprite->show(sequence);
//	//	previousSequence = idleSequence;
//	//}
//	
//	
//	
//	
//	
//
//	//previousSequence = sequence;
//}
