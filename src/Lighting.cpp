#include "Lighting.h"

Lighting::Lighting()
{
	m_lightAmbient = lightColour4(0.0, 0.0, 0.0, 1.0);
	m_lightDiffuse = lightColour4(1.0, 1.0, 1.0, 1.0);
	m_lightSpecular = lightColour4(1.0, 1.0, 1.0, 1.0);
	m_lightPosition = glm::vec4(0.0, 0.0, 1.0, 0.0);
	m_spotDirection = glm::vec3(0.0, 0.0, 1.0);
	m_spotExponent = 0.0f;
	m_spotCutoff = 180.0f;
	m_constantAttenuation = 1.0;
	m_linearAttenuation = 0.0;
	m_quadraticAttenuation = 0.0f;
}

Lighting::Lighting(lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, glm::vec4 position, glm::vec3 spotDirection,
	GLfloat spotExponent, GLfloat spotCutoff, GLfloat constantAttenuation, GLfloat linearAttenuation, GLfloat quadraticAttenuation)
{
	m_lightAmbient = ambient;
	m_lightDiffuse = diffuse;
	m_lightSpecular = specular;
	m_lightPosition = position;
	m_spotDirection = spotDirection;
	m_spotExponent = spotCutoff;
	m_constantAttenuation = constantAttenuation;
	m_linearAttenuation = linearAttenuation;
	m_quadraticAttenuation = quadraticAttenuation;
}