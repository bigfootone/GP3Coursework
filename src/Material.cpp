#include "Material.h"

Material::Material()
{
	m_Ambient = lightColour4(0.2f, 0.2f, 0.2f, 1.0f);
	m_Diffuse = lightColour4(0.8f, 0.8f, 0.8f, 1.0f);
	m_Specular = lightColour4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Emission = lightColour4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Shininess = 0;
}

Material::Material(lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, lightColour4 emission, GLfloat shininess)
{
	m_Ambient = ambient;
	m_Diffuse = diffuse;
	m_Specular = specular;
	m_Emission = emission;
	m_Shininess = shininess;
}