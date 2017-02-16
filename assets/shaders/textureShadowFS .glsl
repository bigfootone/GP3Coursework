#version 330 core

// Interpolated values from the vertex shaders
in vec4 vertexColourOut;
in vec2 vertexTexCoordsOut;
in vec4 ShadowCoord;

// Ouput data
out vec4 FragColour;

// Values that stay constant for the whole mesh.
uniform sampler2D texture0
uniform sampler2DShadow shadowMap;

void main(){

	// Light emission properties
	vec4 LightColor = vec4(1,1,1,1);
	
	// Material properties
	vec4 MaterialDiffuseColor = texture( myTextureSampler, vertexTexCoordsOut );

	float visibility = texture( shadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z)/ShadowCoord.w) );

	FragColour = visibility * MaterialDiffuseColor * LightColor;

}