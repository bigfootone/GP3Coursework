#include "Components\RenderComponent.h"
#include "GameObject.h"

Renderer::Renderer()
{
	type = "render component";
}

Renderer::Renderer(GameObject *tempOwner)
{
	type = "render component";
	owner = tempOwner;
}

Renderer::~Renderer()
{
}

void Renderer::init()
{

}

void Renderer::update(mat4 MVPMat)
{
	MVP = MVPMat;
}

void Renderer::render()
{
	//if (owner->getCurScene()->getActiveShader() != owner->getShader()->getShader())
	//{
		glUseProgram(owner->getShader()->getShader());
		owner->getCurScene()->setActiveShader(owner->getShader()->getShader());
	//}

	if (!owner->getTexture()->getTex2D())
	{
		glDepthMask(GL_FALSE);
	}

	//get the uniform loaction for the MVP
	GLint MVPLocation = glGetUniformLocation(owner->getShader()->getShader(), "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVP));

	if (owner->getTexture()->getTex2D())
	{

		GLuint modelLocation = glGetUniformLocation(owner->getShader()->getShader(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(owner->getModelMatrix()));
		//get the uniform for the texture coords

		GLint texture0Location = glGetUniformLocation(owner->getShader()->getShader(), "material.diffuse");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, owner->getTexture()->getTexture());
		glUniform1i(texture0Location, 0);

	}
	else
	{
		GLint cubeTexLocation = glGetUniformLocation(owner->getShader()->getShader(), "cubeTexture");
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, owner->getTexture()->getTexture());
		glUniform1i(cubeTexLocation, 1);
	}

	/*GLint toonShadeLocation = glGetUniformLocation(owner->getShader()->getShader(), "toonShade");
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_1D, owner->getTexture()->getTexture());
	glUniform1i(toonShadeLocation, 1);*/

	glBindVertexArray(owner->getModel()->getVAO());
	//begin drawing triangle 
	glDrawElements(GL_TRIANGLES, owner->getModel()->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);

	if (!owner->getTexture()->getTex2D())
	{
		glDepthMask(GL_TRUE);
	}

}

string Renderer::getType()
{
	return type;
}