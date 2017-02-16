#version 330 core
in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoords;

out vec3 Normal;
out vec3 FragPos; 
out vec2 TexCoords;
out vec3 cameraDirectionOut;

uniform mat4 MVP;
uniform mat4 model;
uniform vec3 viewPos;

void main()
{
    gl_Position = MVP * vec4(vertexPosition, 1.0f);
    FragPos = vec3(model * vec4(vertexPosition, 1.0f));
  //  Normal = mat3(transpose(inverse(model))) * vertexNormal;  
    Normal = normalize(model * vec4(vertexNormal, 1)).xyz;
	//Normal = model *vec4(vertexNormal, 1);
	cameraDirectionOut = normalize(viewPos - FragPos);
    TexCoords = vertexTexCoords;
} 