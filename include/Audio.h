#pragma once
#include "AL\alut.h"
#include "Common.h"


class Audio
{
public:

	Audio();
	~Audio();

	void createBuffer(string Audiopath);
	void playAudio();
	void stopAudio();
	void loopAudio(bool looping);

private:

	ALuint AudioBuffer;
	ALuint AudioSource;
	string path;

	ALenum error;
};
