#ifndef _WINDOW_H
#define _WINDOW_H

#include "SDL2.h"
#include "OpenGL.h"
#include "Game.h"
#include "FileSystem.h"
#include "KeyboardListener.h"


//extern  IkeyboardListener *keyboard; // this needs to be a vector
extern vector <IkeyboardListener*> keyboardListeners;

void createWindow(string gameName);
void destroyWindow();
void windowLoop();
SDL_Window *getWin();

#endif