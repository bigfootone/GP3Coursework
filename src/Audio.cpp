#include "Audio.h"

Audio::Audio()
{

}

Audio::~Audio()
{

}

void Audio::createBuffer(string Audiopath)
{
	//initialise the environment
	alutInit	(NULL, NULL);

	//load file from path into buffer
	path = ASSET_PATH + AUDIO_PATH + Audiopath;
	AudioBuffer = alutCreateBufferFromFile(path.c_str());

	//Create audio source from buffer
	alGenSources(1, &AudioSource);
	alSourcei(AudioSource, AL_BUFFER, AudioBuffer);

	if ((error = alutGetError()) != AL_NO_ERROR)
	{
		cout << alutGetErrorString(error) << endl;
	}

}

void Audio::playAudio()
{
	//play audio
	alSourcePlay(AudioSource);
}

void Audio::stopAudio()
{
	//stop audio
	alSourceStop(AudioSource);
}