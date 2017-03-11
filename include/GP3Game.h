#ifndef _GP3Game_H
#define _GP3Game_H

#include "Game.h"
#include "Scene.h"

class GP3Game : public GameApp
{
public:
	GP3Game();
	~GP3Game();
	void destroyGame() override;
	bool gameLoop() override;

private:

};

#endif