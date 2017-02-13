#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "FBXLoader.h"
#include "Box.h"
#include "Vertex.h"

class Object
{
public:
	Object();
	Object(string tempName);
	~Object();

	virtual void createBuffer(string modelPath);
	virtual void cleanUp();
	virtual GLuint getVBO();
	virtual GLuint getEBO();
	virtual GLuint getVAO();
	virtual MeshData *getMesh();
	virtual string getName();
	virtual Box *getBoundingBox(){ return boundingBox; };
	virtual void createBuffer();

protected:
	MeshData *currentMesh;
	Box *boundingBox;

	string name;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;
};

#endif