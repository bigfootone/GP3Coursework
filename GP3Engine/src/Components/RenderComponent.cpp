#include "Components\RenderComponent.h"
#include "GameObject.h"
#include "FireballComponent.h"

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
		CHECK_GL_ERROR();
		//glUseProgram(owner->getShader()->getShader());
		owner->getCurScene()->setActiveShader(owner->getShader()->getShader());
		CHECK_GL_ERROR();
		//TODO fix invalid operation
	//}

	if (!owner->getTexture()->getTex2D())
	{
		glDepthMask(GL_FALSE);
		CHECK_GL_ERROR();
	}

	//get the uniform loaction for the MVP
	GLint MVPLocation = glGetUniformLocation(owner->getShader()->getShader(), "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVP));
	CHECK_GL_ERROR();

	if (owner->getTexture()->getTex2D())
	{

		GLuint modelLocation = glGetUniformLocation(owner->getShader()->getShader(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(owner->getModelMatrix()));
		CHECK_GL_ERROR();
		//get the uniform for the texture coords

		//if its a fireball, add lighting
		Lighting *lPtr = FireballComponent::getActiveLight();
		if (lPtr)
		{
			Lighting l = *lPtr;

			GLint uniformLoc = glGetUniformLocation(owner->getShader()->getShader(), "light.diffuse");	//inside light strut - diffuse value
			glUniform3f(uniformLoc, l.m_lightDiffuse.r, l.m_lightDiffuse.g, l.m_lightDiffuse.b);

			uniformLoc = glGetUniformLocation(owner->getShader()->getShader(), "light.ambient");	//inside light strut - ambient value
			glUniform3f(uniformLoc, l.m_lightAmbient.r, l.m_lightAmbient.g, l.m_lightAmbient.b);

			uniformLoc = glGetUniformLocation(owner->getShader()->getShader(), "light.specular");	//inside light strut - specular value
			glUniform3f(uniformLoc, l.m_lightSpecular.r, l.m_lightSpecular.g, l.m_lightSpecular.b);

			uniformLoc = glGetUniformLocation(owner->getShader()->getShader(), "light.position");	//inside light strut - position value
			vec4 pos = l.m_lightPosition;
			glUniform3f(uniformLoc, pos.x, pos.y, pos.z);
		}

		GLint texture0Location = glGetUniformLocation(owner->getShader()->getShader(), "material.diffuse");	//inside material strut - diffuse value
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, owner->getTexture()->getTexture());
		glUniform1i(texture0Location, 0);

		FireballComponent* fireball = (FireballComponent*)owner->getComponents("fireball component");
		if (fireball)
		{
			Material m = fireball->getMaterial();

			GLint uniformLoc = glGetUniformLocation(owner->getShader()->getShader(), "material.specular");	//inside material strut - specular value
			glUniform3f(uniformLoc, m.m_Specular.r, m.m_Specular.g, m.m_Specular.b);

			uniformLoc = glGetUniformLocation(owner->getShader()->getShader(), "material.shininess");	//inside material strut - shininess value
			glUniform1f(uniformLoc, m.m_Shininess);
		}

		CHECK_GL_ERROR();
	}
	else
	{
		GLint cubeTexLocation = glGetUniformLocation(owner->getShader()->getShader(), "cubeTexture");
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, owner->getTexture()->getTexture());
		glUniform1i(cubeTexLocation, 1);
		CHECK_GL_ERROR();
	}


	glBindVertexArray(owner->getModel()->getVAO());
	CHECK_GL_ERROR();
	//begin drawing triangle 
	glDrawElements(GL_TRIANGLES, owner->getModel()->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);
	CHECK_GL_ERROR();

	if (!owner->getTexture()->getTex2D())
	{
		glDepthMask(GL_TRUE);
		CHECK_GL_ERROR();
	}

}

string Renderer::getType()
{
	return type;
}