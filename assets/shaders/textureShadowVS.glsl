#version 330 core

// Input vertex data, different for all executions of this shader.
in vec3 vertexPosition;
in vec2 vertexColour;
in vec3 vertexTexCoords;
in vec3 vertexNormal;

// Output data ; will be interpolated for each fragment.
out vec4 vertexColourOut;
out vec2 vertexTexCoordsOut;
out vec4 ShadowCoord;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 DepthBiasMVP;


void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition,1);
	
	ShadowCoord = DepthBiasMVP * vec4(vertexPosition,1);
	
	// UV of the vertex. No special space for this one.
	vertexTexCoordsOut = vertexTexCoords;
}
