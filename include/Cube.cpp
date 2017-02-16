#include "Cube.h"

Cube::Cube(string tempName)
{
	name = tempName;
};

void Cube::createBuffer()
{
	const int numberOfCubeIndices = 36;
	const int numberOfCubeVerts = 8;

	Vertex cubeVerts[] =
	{
		//front
		{ vec3(-10.0f, 10.0f, 10.0f),		//top left
		vec4(1.0f, 0.0f, 1.0f, 1.0f),
		vec2(0.0f, 0.0f),
		vec3(-0.3f, 0.3f, 0.3f)
		},
		{ vec3(-10.0f, -10.0f, 10.0f),		//bottom left
		vec4(1.0f, 1.0f, 0.0f, 1.0f),
		vec2(0.0f, 1.0f),
		vec3(-0.3f, -0.3f, 0.3f)
		},
		{ vec3(10.0f, -10.0f, 10.0f),		//bottom right
		vec4(0.0f, 1.0f, 1.0f, 1.0f),
		vec2(1.0f, 1.0f),
		vec3(0.3f, -0.3f, 0.3f)
		},
		{ vec3(-10.0f, 10.0f, 10.0f),		//top right 
		vec4(1.0f, 0.0f, 1.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec3(0.3f, 0.3f, 0.3f)
		},
		//back
		{ vec3(-10.0f, 10.0f, -10.0f),		//top left
		vec4(1.0f, 0.0f, 1.0f, 1.0f),
		vec2(0.0f, 0.0f),
		vec3(-0.3f, 0.3f, -0.3f)
		},
		{ vec3(-10.0f, -10.0f, -10.0f),		//bottom left
		vec4(1.0f, 1.0f, 0.0f, 1.0f),
		vec2(0.0f, 1.0f),
		vec3(-0.3f, -0.3f, -0.3f)
		},
		{ vec3(10.0f, -10.0f, -10.0f),		//bottom right
		vec4(0.0f, 1.0f, 1.0f, 1.0f),
		vec2(1.0f, 1.0f),
		vec3(0.3f, -0.3f, -0.3f)
		},
		{ vec3(-10.0f, 10.0f, -10.0f),		//top right 
		vec4(1.0f, 0.0f, 1.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec3(0.3f, 0.3f, -0.3f)
		},
	};

	int cubeIndices[] =
	{
		//front
		0, 1, 2,
		0, 3, 2,
		//left
		4, 5, 1,
		4, 1, 0,
		//right
		3, 7, 2,
		7, 6, 2,
		//bottom
		1, 5, 2,
		6, 2, 5,
		//top
		4, 0, 7,
		0, 7, 3,
		//back
		4, 5, 6,
		4, 7, 6

	};
};
