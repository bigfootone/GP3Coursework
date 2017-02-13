#include "Common.h"
#include "Window.h"

SDL_Window *window;
SDL_GLContext glContext;
IkeyboardListener *keyboard;

void createWindow(string gameName)
{
	GLenum err = GL_NO_ERROR;

	ChangeWorkingDirectory();

	initSDL2();
	initSDL2Image();
	initSDL2TTF();

	//ask for version 4.2 of openGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//create a window 

	window = SDL_CreateWindow(gameName.c_str(), //window title
		SDL_WINDOWPOS_CENTERED, // x position centered
		SDL_WINDOWPOS_CENTERED, //y position centered
		SCREEN_WIDTH, //width in pixels 
		SCREEN_HEIGHT, //height in pixels 
		SDL_WINDOW_OPENGL //flags
		);

	//create an openGL context associated with the window
	glContext = SDL_GL_CreateContext(window);

	//initalisation
	//call our initOpenGL function
	initOpenGL();
	//set our viewport
	setViewport(SCREEN_WIDTH, SCREEN_HEIGHT);


	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in creating window " << err << endl;
	}
}

void destroyWindow()
{
	//clean up in reverse order
	//clean out the buffers 
	//destroy openGL
	SDL_GL_DeleteContext(glContext);
	//destroy window
	SDL_DestroyWindow(window);
	//destroy image Lib
	IMG_Quit();
	//destroy SDL font lib
	TTF_Quit();
	//destroy initalization 
	SDL_Quit();
}

void windowLoop()
		{
	//call swap so that our GL back buffer is displayed
	SDL_GL_SwapWindow(window);
}

SDL_Window *getWin()
{
	return window;
}