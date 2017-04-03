#pragma once


#include "Common.h"

class Material
{
public:

	Material();
	Material(lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, lightColour4 emission, GLfloat  shininess);

	lightColour4 m_Ambient;
	lightColour4 m_Diffuse;
	lightColour4 m_Specular;
	lightColour4 m_Emission;

	GLfloat  m_Shininess;

};