#pragma once

#include "SDL.h"
#include <SDL_mixer.h>
#include <vector>
#include <map>

using namespace std;

class AudioMixer
{
public:
	/*
	* Initializes the AudioMixer by setting up the SDL_mixer
	*/
	AudioMixer();

	/*
	* Adds a sound to a map that can be referenced by string names
	* @param soundName - The name associated with the sound
	* @param fileName - The name of the sound file
	*/
	void addSound(std::string soundName, std::string fileName);

	/*
	* Plays the sound once
	* @param soundName - The name associated with the sound
	*/
	void playSoundOnce(std::string soundName);

	/*
	* Plays the sound repeatedly
	* @param soundName - The name associated with the sound
	*/
	void loopSound(std::string soundName);

	/*
	* Pauses the sound
	* @param soundName - The name associated with the sound
	*/
	void pauseSound(std::string soundName);

	/*
	* Resumes playing the sound
	* @param soundName - The name associated with the sound
	*/
	void resumeSound(std::string soundName);

	/*
	* Stops playing the sound
	* @param soundName - The name associated with the sound
	*/
	void stopPlayingSound(std::string soundName);

	/*
	* Stops playing all sounds that are currently playing
	* @param soundName - The name associated with the sound
	*/
	void stopPlayingAllSounds();

	/*
	* Cleans up the AudioMixer and frees memory
	*/
	~AudioMixer();

private:
	/*
	* A counter to assign a unique channel number to each sound added
	*/
	int channels;

	/*
	* Map to hold a list of sounds associated with the sound name
	*/
	std::map<std::string, Mix_Chunk *> soundList;

	/*
	* Map to hold a list of channels associated with sound name
	*/
	std::map<std::string, int> channelsList;
};

