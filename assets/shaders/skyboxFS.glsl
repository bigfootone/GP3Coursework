#version 150

out vec4 FragColour;
in vec3 vertexTexCoordsOut;
uniform samplerCube cubeTexture;

void main()
{
	FragColour = texture(cubeTexture, vertexTexCoordsOut);
	//FragColour = vec4(1.0f, 0.0f, 0.0f, 0.0f);
}