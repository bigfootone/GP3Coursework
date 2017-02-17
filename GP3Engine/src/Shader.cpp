#include "Shader.h"

//load it from mem buff
GLuint loadShaderFromMemory(const char *pMem, SHADER_TYPE shaderType)
{
	GLuint program = glCreateShader(shaderType);
	glShaderSource(program, 1, &pMem, NULL);
	glCompileShader(program);
	return program;
}

GLuint loadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType)
{
	string fileContents;
	ifstream file;
	file.open(filename.c_str(), std::ios::in);
	if (!file)
	{
		cout << "File could not be loaded" << endl;
		return 0;
	}

	//calculate file size
	if (file.good())
	{
		file.seekg(0, std::ios::end);
		unsigned long len = file.tellg();
		file.seekg(std::ios::beg);
		if (len == 0)
		{
			std::cout << "file has no contents" << std::endl;
			return 0;
		}
		fileContents.resize(len);
		file.read(&fileContents[0], len);
		file.close();
		GLuint program = loadShaderFromMemory(fileContents.c_str(), shaderType);
		return program;
	}

	return 0;
}

bool checkForCompilerErrors(GLuint shaderProgram)
{
	GLint ifCompiled = 0;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &ifCompiled);
	if (ifCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		//the maxLength included the null character
		string infoLog;
		infoLog.resize(maxLength);
		glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		cout << "shader not compiled" << infoLog << endl;

		//we dont need the shader anymore 
		glDeleteShader(shaderProgram);
		return true;
	}
	return false;
}

bool checkForLinkErrors(GLuint program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		//the max lenght includes the null character
		string infoLog;
		infoLog.resize(maxLength);
		glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		cout << "shader not linked " << infoLog << endl;
		//we dont need the shader anymore 
		glDeleteProgram(program);
		return true;
	}
	return false;
}

Shader::Shader()
{
}

Shader::Shader(string tempName)
{
	name = tempName;
}

Shader::~Shader()
{
}

void Shader::attatchVertexShader(string ShaderPath)
{
	string Path = ASSET_PATH + SHADER_PATH + ShaderPath;
	vertexShader = loadShaderFromFile(Path, VERTEX_SHADER);
	checkForCompilerErrors(vertexShader);
}

void Shader::attatchFragmentShader(string ShaderPath)
{
	string Path = ASSET_PATH + SHADER_PATH + ShaderPath;
	fragmentShader = loadShaderFromFile(Path, FRAGMENT_SHADER);
	checkForCompilerErrors(fragmentShader);
}

void Shader::createShader()
{
	finalShader = glCreateProgram();
	glAttachShader(finalShader, vertexShader);
	glAttachShader(finalShader, fragmentShader);

	glBindAttribLocation(finalShader, 0, "vertexPosition");
	glBindAttribLocation(finalShader, 1, "vertexColour");
	glBindAttribLocation(finalShader, 2, "vertexTexCoords");
	glBindAttribLocation(finalShader, 3, "vertexNormal");

	glLinkProgram(finalShader);
	checkForLinkErrors(finalShader);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in creating shader " << err << endl;
	}

}

GLuint Shader::create1DTexture(float *pData, int width)
{
	GLuint texture1d;
	glActiveTexture(GL_TEXTURE2);
	glGenTextures(1, &texture1d);
	glBindTexture(GL_TEXTURE_1D, texture1d);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, width, 0, GL_RGB, GL_FLOAT, pData);	
	return texture1d;
}

void Shader::createToonTexture(float *pData, int width)
{
	toonTextureMap = create1DTexture(pData, width);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D);

}

GLuint Shader::getShader()
{
	return finalShader;
}

string Shader::getName()
{
	return name;
}

void Shader::cleanUp()
{
	glDeleteProgram(finalShader);
}