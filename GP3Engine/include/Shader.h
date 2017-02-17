#ifndef Shader_h
#define Shader_h

#include "Common.h"
#include "Texture.h"

enum SHADER_TYPE
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

GLuint loadShaderFromMemory(const char *pMem, SHADER_TYPE shaderType);
GLuint loadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType);
bool checkForCompilerErrors(GLuint shaderProgram);
bool checkForLinkErrors(GLuint program);

class Shader
{
public:
	Shader();
	Shader(string tempName);
	~Shader();
	virtual void bind(){glUseProgram(ShaderProgram);};
	virtual void unbind(){};
	void attatchVertexShader(string shaderPath);
	void attatchFragmentShader(string shaderPath);
	void createShader();
	GLuint create1DTexture(float *pData, int width);
	void createToonTexture(float *pData, int width);
	GLuint getShader();
	string getName();
	void cleanUp();

protected:
	string name;
	GLuint ShaderProgram;
	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;
	GLuint finalShader = 0;
	GLuint toonTextureMap = 0;
};

#endif