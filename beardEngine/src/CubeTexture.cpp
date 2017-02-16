#include "CubeTexture.h"

GLuint loadCubeMapFace(const string& filename, GLenum face)
{
	SDL_Surface *imageSurface = IMG_Load(filename.c_str());

	if (!imageSurface)
	{
		cout << "Can't load image" << filename << " " << IMG_GetError();
	}
	GLint nOfColours = imageSurface->format->BytesPerPixel;

	GLenum textureFormat = GL_RGB;
	GLenum internalFormat = GL_RGB8;

	if (nOfColours == 4) //contains an alpha channel
	{
		if (imageSurface->format->Rmask == 0x000000ff)
		{
			textureFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
		}
		else
		{
			textureFormat = GL_BGRA;
			internalFormat = GL_RGBA8;
		}
	}
	else if (nOfColours == 3)
	{
		if (imageSurface->format->Rmask == 0x000000ff)
		{
			textureFormat = GL_RGB;
			internalFormat = GL_RGB8;
		}
		else
		{
			textureFormat = GL_BGR;
			internalFormat = GL_RGB8;
		}
	}
	else
	{
		cout << "warning: the image is not true colour..this will probable break" << endl;
		return 0;
	}

	glTexImage2D(face, 0, internalFormat, imageSurface->w, imageSurface->h, 0, textureFormat, GL_UNSIGNED_BYTE, imageSurface->pixels);

	SDL_FreeSurface(imageSurface);
}

GLuint loadCubeMap(const string& filenamePosZ, const string& filenameNegZ, const string& filenamePosX, const string& filenameNegX, const string& filenamePosY, const string& filenameNegY)
{
	GLuint textureID;
	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	loadCubeMapFace(filenamePosX, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	loadCubeMapFace(filenameNegX, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	loadCubeMapFace(filenamePosY, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	loadCubeMapFace(filenameNegY, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	loadCubeMapFace(filenamePosZ, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	loadCubeMapFace(filenameNegZ, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);



	return textureID;
}

void CubeTexture::loadSkyBoxTextures(const string& filenamePosZ, const string& filenameNegZ, const string& filenamePosX, const string& filenameNegX, const string& filenamePosY, const string& filenameNegY)
{
	textureMap = loadCubeMap(filenamePosZ, filenameNegZ, filenamePosX, filenameNegX, filenamePosY, filenameNegY);
}