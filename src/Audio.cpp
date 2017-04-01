#include "Audio.h"

Audio::Audio()
{

}

Audio::~Audio()
{

}

void Audio::createBuffer(string Audiopath)
{
	path = ASSET_PATH + TEXTURE_PATH + Audiopath;
	AudioBuffer = alutCreateBufferFromFile(path.c_str());
	alGenSources(1, &AudioSource);
	alSourcei(AudioSource, AL_BUFFER, AudioBuffer);
}

void Audio::playAudio()
{
	alSourcePlay(AudioSource);
}

void Audio::stopAudio()
{
	alSourceStop(AudioSource);
}