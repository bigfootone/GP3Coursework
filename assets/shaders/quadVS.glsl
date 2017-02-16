#version 330 core

// Input vertex data, different for all executions of this shader.
in vec3 vertexPosition;

// Output data ; will be interpolated for each fragment.
out vec2 vertexTexCoords;

void main(){
	gl_Position = vec4(vertexPosition, 1);
	vertexTexCoords = (vertexPosition.xy + vec2(1, 1)) / 2.0;
}

