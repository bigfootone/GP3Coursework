#include "Cube.h"

Cube::Cube(string tempName)
{
	name = tempName;
};

void Cube::createBuffer()
{
	const int numberOfCubeIndices = 36;
	const int numberOfCubeVerts = 8;
	currentMesh = new MeshData();

		vector <Vertex> cubeVerts = 
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
		{ vec3(10.0f, 10.0f, 10.0f),		//top right 
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
		{ vec3(10.0f, 10.0f, -10.0f),		//top right 
		vec4(1.0f, 0.0f, 1.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec3(0.3f, 0.3f, -0.3f)
		},
	};

		vector<int> cubeIndices =
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

		for each (auto var in cubeVerts)
		{
			currentMesh->vertices.push_back(var);
		}

		for each (auto var in cubeIndices)
		{
			currentMesh->indices.push_back(var);
		}

		//gen vertex array object
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//create vertex buffer object
		glGenBuffers(1, &VBO);
		//make the VBO active
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//copy vertex data to VBO
		glBufferData(GL_ARRAY_BUFFER, currentMesh->getNumVerts()*sizeof(Vertex), currentMesh->vertices.data(), GL_STATIC_DRAW);

		//create element buffer object 
		glGenBuffers(1, &EBO);
		//make the EBO active
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//copy the index date to the EBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, currentMesh->getNumIndices()*sizeof(int), currentMesh->indices.data(), GL_STATIC_DRAW);

		//tell the shader that 0 is the position element 
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
		//send the colour to the shader
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
		//send the text coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3)+sizeof(vec4)));
		//send normals to buffer
		glDisableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3)+sizeof(vec4)+sizeof(vec2)));

		//create bounding box
		boundingBox = new Box();
		boundingBox->setPoints(currentMesh);

		GLenum err = GL_NO_ERROR;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			//Process/log the error.
			cout << "error in creating object buffer for cube" << err << endl;
		}

};