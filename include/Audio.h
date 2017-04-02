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

private:

	ALuint AudioBuffer;
	ALuint AudioSource;
	string path;

	ALenum error;
};
