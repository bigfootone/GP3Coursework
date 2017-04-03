#pragma once

#include "Common.h";

class Lighting
{

public:

	Lighting();
	Lighting(lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, glm::vec4 position, glm::vec3 spotDirection,
			GLfloat spotExponent, GLfloat spotCutoff, GLfloat constantAttenuation, GLfloat linearAttenuation, GLfloat quadraticAttenuation);

	lightColour4 m_lightDiffuse;
	lightColour4 m_lightAmbient;
	lightColour4 m_lightSpecular;

	glm::vec4 m_lightPosition;
	glm::vec3 m_spotDirection;

	GLfloat  m_spotExponent;
	GLfloat  m_spotCutoff;
	GLfloat  m_constantAttenuation;
	GLfloat  m_linearAttenuation;
	GLfloat  m_quadraticAttenuation;
};

