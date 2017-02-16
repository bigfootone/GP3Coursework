#version 330

// Interpolated values from the vertex shaders
//in vec4 vertexColourOut;
//in vec2 vertexTexCoordsOut;

//in vec3 Position_worldspace;

//in vec3 Normal_cameraspace;
//in vec3 EyeDirection_cameraspace;

//in vec3 LightDirection_cameraspace;

//in vec4 ShadowCoord;


in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPosition;

// Ouput data
out vec4 FragColour;

// Values that stay constant for the whole mesh.
uniform mat4 M;
uniform vec3 cameraPosition;

uniform sampler2D texture0;

uniform float materialShininess;
uniform vec3 materialSpecularColor;

uniform struct Light{
	vec3 position;
	vec3 intensities;
	float attenuation;
	float ambientCoefficient;
} light;

//uniform sampler2DShadow shadowMap;

/*vec2 poissonDisk[16] = vec2[](
	vec2(-0.94201624, -0.39906216),
	vec2(0.94558609, -0.76890725),
	vec2(-0.094184101, -0.92938870),
	vec2(0.34495938, 0.29387760),
	vec2(-0.91588581, 0.45771432),
	vec2(-0.81544232, -0.87912464),
	vec2(-0.38277543, 0.27676845),
	vec2(0.97484398, 0.75648379),
	vec2(0.44323325, -0.97511554),
	vec2(0.53742981, -0.47373420),
	vec2(-0.26496911, -0.41893023),
	vec2(0.79197514, 0.19090188),
	vec2(-0.24188840, 0.99706507),
	vec2(-0.81409955, 0.91437590),
	vec2(0.19984126, 0.78641367),
	vec2(0.14383161, -0.14100790)
	);*/

// Returns a random number based on a vec3 and an int.
/*float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed, i);
	float dot_product = dot(seed4, vec4(12.9898, 78.233, 45.164, 94.673));
	return fract(sin(dot_product) * 43758.5453);
}*/

void main(){
	
	vec3 normal = normalize(transpose(inverse(mat3(M))) * fragNormal);
    
	vec3 surfacePos = vec3(M * vec4(fragPosition, 1));
    
	vec4 surfaceColor = texture(texture0, fragTexCoord);
    
	vec3 surfaceToLight = normalize(light.position - surfacePos);
    
	vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);

	//ambient
    
	vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

 
   
	//diffuse
    
	float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    
	vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;

	//specular

  	float specularCoefficient = 500;
	//specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);


    	if(diffuseCoefficient > 0.0)

	{        
		specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);

	}    
	vec3 specular = specularCoefficient * materialSpecularColor * light.intensities;

 	//attenuation

    	float distanceToLight = length(light.position - surfacePos);
    
	float attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));


    
	//linear color (color before gamma correction)
    
	vec3 linearColor = ambient + attenuation*(diffuse + specular);
    

    
	//final color (after gamma correction)
    
	vec3 gamma = vec3(1.0/2.2);
    
	FragColour = vec4(pow(linearColor, gamma), surfaceColor.a);
	

	// Light emission properties
	//vec4 LightColor = vec4(0, 0, 0.2, 0.2);
	//float LightPower = 50.0f;

	// Material properties
	//vec4 MaterialDiffuseColor = texture(texture0, vertexTexCoordsOut);
	//vec4 MaterialAmbientColor = vec4(0.1, 0.1, 0.1, 1.0) * MaterialDiffuseColor;
	//vec4 MaterialSpecularColor = vec4(0.3, 0.3, 0.3, 1.0);

	// Distance to the light
	//float distance = length( LightPosition_worldspace - Position_worldspace );

	// Normal of the computed fragment, in camera space
	//vec3 n = normalize(Normal_cameraspace);

	// Direction of the light (from the fragment to the light)
	//vec3 l = normalize(LightDirection_cameraspace);

	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendiular to the triangle -> 0
	//  - light is behind the triangle -> 0
	//float cosTheta = clamp(dot(n, l), 0, 1);
	


	// Eye vector (towards the camera)
	//vec3 E = normalize(EyeDirection_cameraspace);

	// Direction in which the triangle reflects the light
	//vec3 R = reflect(-l, n);

	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	//float cosAlpha = clamp(dot(E, R), 0, 1);
	
	
	/*float visibility = 1.0;

	// Fixed bias, or...
	//float bias = 0.005;

	// ...variable bias
	// float bias = 0.005*tan(acos(cosTheta));
	// bias = clamp(bias, 0,0.01);



	// Sample the shadow map 4 times
	for (int i = 0; i<4; i++){
		// use either :
		//  - Always the same samples.
		//    Gives a fixed pattern in the shadow, but no noise
		int index = i;
		//  - A random sample, based on the pixel's screen location. 
		//    No banding, but the shadow moves with the camera, which looks weird.
		// int index = int(16.0*random(gl_FragCoord.xyy, i))%16;
		//  - A random sample, based on the pixel's position in world space.
		//    The position is rounded to the millimeter to avoid too much aliasing
		// int index = int(16.0*random(floor(Position_worldspace.xyz*1000.0), i))%16;

		// being fully in the shadow will eat up 4*0.2 = 0.8
		// 0.2 potentially remain, which is quite dark.
		visibility -= 0.2*(1.0 - texture(shadowMap, vec3(ShadowCoord.xy + poissonDisk[index] / 700.0, (ShadowCoord.z - bias) / ShadowCoord.w)));
	}*/

	// For spot lights, use either one of these lines instead.
	// if ( texture( shadowMap, (ShadowCoord.xy/ShadowCoord.w) ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w )
	// if ( textureProj( shadowMap, ShadowCoord.xyw ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w )

	//FragColour = 	MaterialAmbientColor + 
		//	MaterialDiffuseColor*LightColor*LightPower*cosTheta/(distance*distance) + 
		//	MaterialSpecularColor*LightColor*LightPower* pow(cosAlpha,5)/(distance*distance);

//FragColour = MaterialDiffuseColor*LightPower*LightColor + MaterialAmbientColor + MaterialSpecularColor*LightPower*LightColor;

//FragColour = texture(texture0, vertexTexCoordsOut);

//FragColour = MaterialAmbientColor + 
	//	MaterialDiffuseColor*LightColor*LightPower*cosTheta /(distance*distance) + 
		//MaterialSpecularColor*LightColor*LightPower;//*pow(cosAlpha, 5)/(distance*distance);
}


