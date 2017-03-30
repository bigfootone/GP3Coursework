#include "GP3Game.h"
#include "SpaceScene.h"

GP3Game::GP3Game()
{
	//create the main scene
	currentScene = new SpaceScene("Space");
	//main scene to the current scene (this could be usefull for multiple scenes (maybe))
	keyboardListeners.push_back(currentScene);

	currentScene->createScene();
}

GP3Game::~GP3Game()
{

}

void GP3Game::destroyGame()
{
	currentScene->destroyScene();
}

bool GP3Game::gameLoop()
{
	//value to hold the event generated by SDL
	SDL_Event event;
	//while we still have events in the queue
	while (SDL_PollEvent(&event))
	{
		//get event type
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			//set our bool which controls the loop to false
			return false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			for each (auto var in keyboardListeners)
			{
				var->onKeyDown(event.key.keysym.sym);
			}
		}
		if (event.type == SDL_KEYUP)
		{
			for each (auto var in keyboardListeners)
			{
				var->onkeyUp(event.key.keysym.sym);
			}
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			for each (auto var in keyboardListeners)
			{
				var->mouseMove(event.motion);
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			for each (auto var in keyboardListeners)
			{
				var->mouseDown(event.button);
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			for each (auto var in keyboardListeners)
			{
				var->mouseUp(event.button);
			}
		}
	}

	currentScene->SceneLoop();

	return true;
}