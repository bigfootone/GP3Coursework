#ifndef _GP2COURSEWORKGAME_H
#define _GP2COURSEWORKGAME_H

#include "Game.h"
#include "HoloRoomScene.h"

class GP2CourseWorkGame : public GameApp
{
public:
	GP2CourseWorkGame();
	~GP2CourseWorkGame();
	void destroyGame() override;
	bool gameLoop() override;

private:

};

#endif