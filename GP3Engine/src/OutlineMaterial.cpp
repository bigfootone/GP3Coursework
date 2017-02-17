#include "OutlineMaterial.h"

OutlineMaterial::OutlineMaterial()
{

}

OutlineMaterial::OutlineMaterial(string tempName)
{
	name = tempName;
}

OutlineMaterial::~OutlineMaterial()
{

}

void OutlineMaterial::bind()
{
	Shader::bind();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDepthMask(GL_FALSE);
}

void OutlineMaterial::unbind()
{
	Shader::unbind();
	glDepthMask(GL_TRUE);
	glDisable(GL_CULL_FACE);
}