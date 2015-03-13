#include "AudioMixer.h"
#include <string>

AudioMixer::AudioMixer()
{
	channels = 0;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void AudioMixer::addSound(std::string soundName, std::string fileName)
{
	Mix_Chunk *sound;

	sound = Mix_LoadWAV(fileName.c_str());

	if (sound == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	channels++;

	soundList[soundName] = sound;
	channelsList[soundName] = channels;
}

void AudioMixer::playSoundOnce(std::string soundName)
{
	Mix_PlayChannel(channelsList[soundName], soundList[soundName], 0);
}

void AudioMixer::loopSound(std::string soundName)
{
	Mix_PlayChannel(channelsList[soundName], soundList[soundName], -1);
}

void AudioMixer::pauseSound(std::string soundName)
{
	Mix_Pause(channelsList[soundName]);
}

void AudioMixer::resumeSound(std::string soundName)
{
	Mix_Resume(channelsList[soundName]);
}

void AudioMixer::stopPlayingSound(std::string soundName)
{
	Mix_HaltChannel(channelsList[soundName]);
}

void AudioMixer::stopPlayingAllSounds()
{
	Mix_HaltChannel(-1);
}

bool AudioMixer::isSoundPlaying(string soundName)
{
	bool result = Mix_Playing(channelsList[soundName]);

	return result;
}

void AudioMixer::addMusic(std::string musicName, std::string fileName)
{
	Mix_Music *music;

	music = Mix_LoadMUS(fileName.c_str());

	if (music == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	musicList[musicName] = music;
}

void AudioMixer::playMusic(std::string musicName)
{
	Mix_PlayMusic(musicList[musicName], -1);
}

void AudioMixer::pauseMusic()
{
	Mix_PauseMusic();
}

void AudioMixer::resumeMusic()
{
	Mix_ResumeMusic();
}

void AudioMixer::stopMusic()
{
	Mix_HaltMusic();
}

bool AudioMixer::isMusicPlaying()
{
	return Mix_PlayingMusic();
}

bool AudioMixer::isMusicPaused()
{
	return Mix_PausedMusic();
}

AudioMixer::~AudioMixer(void)
{
	soundList.clear();
	channelsList.clear();

	Mix_CloseAudio();
}
