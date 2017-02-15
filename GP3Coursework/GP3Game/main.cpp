#include "Window.h"
#undef main
#include "GP2CourseWorkGame.h"



int main(int argc, char * arg[])
{

	bool run = true;

	createWindow("GP3Game");

	GameApp *curGame = new GP2CourseWorkGame();

	while (run)
	{
		if (!curGame->gameLoop())
		{
			run = false;
		}
	}

	curGame->destroyGame();
	destroyWindow();

	return 0;
}
vector <IkeyboardListener*> keyboardListeners;