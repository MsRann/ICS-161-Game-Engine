
#include "Background.h"
//#include "Scientist.h"
#include "SceneManager.h"
#include "GameObject.h"

#include <Windows.h>
#include "SDL_image.h"
#include "SDL.h"
//#include "cleanup.h"
#include "res_path.h"
#include "AudioMixer.h"
#include "AI.h"
#include "Button.h"
#include "Texty.h"

//#include "ResManager.h"
#include <string>
#include <iostream>
#include <sstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv){

	//Initializes everything and errors if failure
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	//Initializes image stuff? Quits if failure
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		SDL_Quit();
		return 1;
	}

	//Creates a window
	SDL_Window *window = SDL_CreateWindow("Game Demo", 800, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr){
		SDL_Quit();
		return 1;
	}

	//Creates renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		//cleanup(window);
		SDL_Quit();
		return 1;
	}
	std::string resPath = getResourcePath("GameTest");
	
	std::string spritesheetLocation = resPath + "Trainers.png";//"C:\\Users\\Jake\\Desktop\\SDL\\MyProjects\\res\\GameTest\\Trainers.png";

	SDL_Surface* spritesheetTestSurface = IMG_Load(spritesheetLocation.c_str());
	SDL_SetColorKey(spritesheetTestSurface, 1, SDL_MapRGB(spritesheetTestSurface->format, 255, 255, 255));
	SDL_Texture *spritesheetTest = SDL_CreateTextureFromSurface(renderer, spritesheetTestSurface);
	//SDL_Texture *spritesheetTest = IMG_LoadTexture(renderer, spritesheetLocation.c_str());

	if (spritesheetTest == nullptr){
		//cleanup(spritesheetTest, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	//////////////////////////////////Testing SceneManager//////////////////////////////////////
	std::string LevelOneImage = resPath + "static_map.png";
	std::string LevelTwoImage = resPath + "BowsersCastle.png";
	Background LevelOneBackground = Background(LevelOneImage, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
	Background LevelTwoBackground = Background(LevelTwoImage, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
	SceneManager sceneManager = SceneManager(renderer);
	sceneManager.addSceneToSceneMap("Level One", &LevelOneBackground);
	sceneManager.addSceneToSceneMap("Level Two", &LevelTwoBackground);


	//Scientist Joe = Scientist(spritesheetTest, renderer, 200, 100);
	//Scientist Frank = Scientist(spritesheetTest, renderer, 100, 100);
	//Scientist Bob = Scientist(spritesheetTest, renderer, 300, 300, true);
	//Scientist Bob1 = Scientist(spritesheetTest, renderer, 300, 100, true);
	//Scientist Bob2 = Scientist(spritesheetTest, renderer, 300, 150, true);
	//Scientist Bob3 = Scientist(spritesheetTest, renderer, 300, 200, true);
	//Scientist Bob4 = Scientist(spritesheetTest, renderer, 300, 250, true);
	//Scientist Bob5 = Scientist(spritesheetTest, renderer, 300, 50, true);
	Sprite Joe = Sprite("Joe",100, 100, 14, 20, renderer);
	Sprite Jim = Sprite("Jim",300, 300, 14, 20, renderer);
	Sprite Robert = Sprite("Robert",400, 400, 14, 20, renderer);
	Sprite Bob = Sprite("Bob",200, 200, 14, 20, renderer);
	sceneManager.addGameObjectToScene("Level One", &Joe);
	sceneManager.addGameObjectToScene("Level Two", &Joe);
	sceneManager.addGameObjectToScene("Level One", &Jim);
	sceneManager.addGameObjectToScene("Level One", &Robert);
	sceneManager.addGameObjectToScene("Level Two", &Bob);

	//Sprite* Joe = new Sprite(x, y, 23, 26, renderer);

	for (int i = 0; i < 3; i++){


		Bob.addFrameToSequence("walk down", Bob.makeFrame(spritesheetTest, 18, 389 + (i * 30), 0.3));
		Bob.addFrameToSequence("walk up", Bob.makeFrame(spritesheetTest, 78, 389 + (i * 30), 0.3));
		Bob.addFrameToSequence("walk right", Bob.makeFrame(spritesheetTest, 109, 389 + (i * 30), 0.3));
		Bob.addFrameToSequence("walk left", Bob.makeFrame(spritesheetTest, 49, 389 + (i * 30), 0.3));

		Joe.addFrameToSequence("walk down", Joe.makeFrame(spritesheetTest, 18, 389 + (i * 30), 0.3));
		Joe.addFrameToSequence("walk up", Joe.makeFrame(spritesheetTest, 78, 389 + (i * 30), 0.3));
		Joe.addFrameToSequence("walk right", Joe.makeFrame(spritesheetTest, 109, 389 + (i * 30), 0.3));
		Joe.addFrameToSequence("walk left", Joe.makeFrame(spritesheetTest, 49, 389 + (i * 30), 0.3));

		
		Jim.addFrameToSequence("walk down", Jim.makeFrame(spritesheetTest, 18, 389 + (i * 30), 0.3));
		Jim.addFrameToSequence("walk up", Jim.makeFrame(spritesheetTest, 78, 389 + (i * 30), 0.3));
		Jim.addFrameToSequence("walk right", Jim.makeFrame(spritesheetTest, 109, 389 + (i * 30), 0.3));
		Jim.addFrameToSequence("walk left", Jim.makeFrame(spritesheetTest, 49, 389 + (i * 30), 0.3));

		
		Robert.addFrameToSequence("walk down", Robert.makeFrame(spritesheetTest, 18, 389 + (i * 30), 0.3));
		Robert.addFrameToSequence("walk up", Robert.makeFrame(spritesheetTest, 78, 389 + (i * 30), 0.3));
		Robert.addFrameToSequence("walk right", Robert.makeFrame(spritesheetTest, 109, 389 + (i * 30), 0.3));
		Robert.addFrameToSequence("walk left", Robert.makeFrame(spritesheetTest, 49, 389 + (i * 30), 0.3));

	}
	Bob.setSequence("walk up");
	Bob.update();

	Jim.setSequence("walk right");
	Jim.update();

	Robert.setSequence("walk left");
	Robert.update();

	Joe.setSequence("walk down");
	Joe.update();

	AI ai = AI(&Robert, &Joe);
	AI ai1 = AI(&Jim, &Joe);
	AI ai2 = AI(&Bob, &Joe);
	//sceneManager.addGameObjectToScene("Level Two", &Frank);
	//sceneManager.addGameObjectToScene("Level One", &Bob);
	//sceneManager.addGameObjectToScene("Level One", &Bob1);
	//sceneManager.addGameObjectToScene("Level One", &Bob2);
	//sceneManager.addGameObjectToScene("Level One", &Bob3);
	//sceneManager.addGameObjectToScene("Level One", &Bob4);
	//sceneManager.addGameObjectToScene("Level One", &Bob5);
	//sceneManager.addScientistToScene("Level One", &Frank);
	//sceneManager.addScientistToScene("Level One", &Bob);


	//Initial setup to show the background before input is even collected
	//Background image = Background("static_map.png", SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
	//image.renderBackground();

	//Scientist Joe = Scientist(spritesheetTest, renderer, 200, 100);
	//Scientist Frank = Scientist(spritesheetTest, renderer, 100, 100);
	//Scientist Bob = Scientist(spritesheetTest, renderer, 300, 300);

	// ADDING AUDIO SOUNDS
	AudioMixer *mixer = new AudioMixer();
	mixer->addSound("footsteps", "footsteps_AMP.wav");
	mixer->addMusic("intro", "adventure.mp3");
	mixer->addMusic("haunted", "haunted_house.mp3");
	mixer->playMusic("intro");

	// ADDING TEXT
	Texty* sceneTitle = new Texty(renderer, resPath + "Spaceship Bullet.ttf", 36, true, { 196, 32, 32, 0 });
	std::string sceneName = "The Laboratory";

	SDL_RenderPresent(renderer);

	SDL_Event e;
	bool quit = false;
	
	bool isPressed = false; //Will let renderScientist know if it should be in idle or moving.
	bool ChangeLevel = false;

	//Joe.renderScientist(spriteDirection, false);

	//const std::string 
	

	SDL_Rect JoeBorder = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	Joe.setBorder(&JoeBorder);

	// DEON'S BUTTON CODE
	int x = SCREEN_WIDTH - 50, y = SCREEN_HEIGHT - 50, w = 50, h = 50;
	std::function<void()> f = [&]() 
	{
		ChangeLevel = !ChangeLevel;
		if (!ChangeLevel)
		{
			mixer->playMusic("intro");
			sceneName = "The Laboratory";
		}
		else
		{
			mixer->playMusic("haunted");
			sceneName = "The Haunted Mansion";
		}
	};
	Button b(renderer, resPath + "button.png", f);

	b.setDimension(x, y, w, h);

	std::string spriteDirection = "hi mom";
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			isPressed = false; // resets

			if (e.type == SDL_KEYDOWN){
				float movex = 0;
				float movey = 0;

				if (e.key.keysym.sym == SDLK_d)
				{
					//ChangeLevel = true;
					Joe.setSequence("walk right");
					movex = 5;

					if (!mixer->isSoundPlaying("footsteps"))
						mixer->playSoundOnce("footsteps");
				}
				if (e.key.keysym.sym == SDLK_a)
				{
					Joe.setSequence("walk left");
					movex = -5;
					if (!mixer->isSoundPlaying("footsteps"))
						mixer->playSoundOnce("footsteps");
				}
				if (e.key.keysym.sym == SDLK_w)
				{
					Joe.setSequence("walk up");
					movey = -5;
					if (!mixer->isSoundPlaying("footsteps"))
						mixer->playSoundOnce("footsteps");
				}
				if (e.key.keysym.sym == SDLK_s)
				{
					Joe.setSequence("walk down");
					movey = 5;
					if (!mixer->isSoundPlaying("footsteps"))
						mixer->playSoundOnce("footsteps");
				}
				if (e.key.keysym.sym == SDLK_q)
				{
					Joe.setSequence("walk up");
					movey = -5;
					movex = -5;
					if (!mixer->isSoundPlaying("footsteps"))
						mixer->playSoundOnce("footsteps");
				}
				if (e.key.keysym.sym == SDLK_e)
				{
					Joe.setSequence("walk down");
					movey = -5;
					movex = 5;
					if (!mixer->isSoundPlaying("footsteps"))
						mixer->playSoundOnce("footsteps");
				}
				if (e.key.keysym.sym == SDLK_z)
				{
					Joe.setSequence("walk down");
					movey = 5;
					movex = -5;
					if (!mixer->isSoundPlaying("footsteps"))
						mixer->playSoundOnce("footsteps");
				}
				if (e.key.keysym.sym == SDLK_x)
				{
					Joe.setSequence("walk down");
					movey = 5;
					movex = 5;
					if (!mixer->isSoundPlaying("footsteps"))
						mixer->playSoundOnce("footsteps");
				}
				if (e.key.keysym.sym == SDLK_p)
				{
					//If there is no music playing
					if (!mixer->isMusicPlaying())
					{
						if (!ChangeLevel)
							mixer->playMusic("intro");
						if (ChangeLevel)
							mixer->playMusic("haunted");
					}
					//If music is being played
					else
					{
						//If the music is paused
						if (mixer->isMusicPaused())
						{
							//Resume the music
							mixer->resumeMusic();
						}
						//If the music is playing
						else
						{
							//Pause the music
							mixer->pauseMusic();
						}
					}
				}

				if (movex != 0 || movey != 0){
					Joe.move_normalized(movex, movey, 1.0f);
				}	
			}
			// DEON'S BUTTON CODE
			b.handleEvents(&e);
		}

		// Clear the scene, Render the scene
		SDL_RenderClear(renderer);
		if (ChangeLevel == true){
			ai2.action();
			sceneManager.getScene("Level Two").applyCollisions();
			sceneManager.updateAll("Level Two");
			sceneManager.renderAll("Level Two", spriteDirection, isPressed);
		}
		else{
			ai.action();
			ai1.action();
			sceneManager.getScene("Level One").applyCollisions();
			sceneManager.updateAll("Level One");
			sceneManager.renderAll("Level One", spriteDirection, isPressed);
		}
		// DEON'S BUTTON CODE
		b.setDimension(x, y, w, h);
		b.drawButton();

		if (!ChangeLevel)
			sceneTitle->write(sceneName.c_str(), SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 40);
		else
			sceneTitle->write(sceneName.c_str(), SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT - 40);
		
		SDL_RenderPresent(renderer);	
	}

	
	IMG_Quit();


	SDL_Quit();

	return 0;
}