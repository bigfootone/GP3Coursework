#version 130

in vec3 vertexPosition;
in vec4 vertexColour;
in vec2 vertexTexCoords;

uniform mat4 MVP;

out vec4 vertexColourOut;
out vec2 vertexTexCoordsOut;

void main()
{
	gl_Position = MVP * vec4(vertexPosition, 1.0);
	vertexColourOut = vertexColour;
	vertexTexCoordsOut = vertexTexCoords;
}