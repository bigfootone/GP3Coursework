#include "OpenGL.h"
#include "Common.h"

void checkError(const char *file, int line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		printf("%s:%d - GL Error: %s\n", file, line, gluErrorString(err));
}

//function to initalise OpenGL
void initOpenGL()
{
	glewExperimental = GL_TRUE;

	//smopth shading
	glShadeModel(GL_SMOOTH);

	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//clear the depth buffer to 1.0
	glClearDepth(1.0f);

	//enable depth testing
	glEnable(GL_DEPTH_TEST);

	//the depth test to use
	glDepthFunc(GL_LEQUAL);

	//turn on best perspective correction
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Need to normalize the normal vectors for lighting calculations
	glEnable(GL_NORMALIZE);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/*Problem: glewInit failed, something is SERIOUSLY wrong*/
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
}

//function to set/reset viewport
void setViewport(int width, int height)
{
	//set up viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

 