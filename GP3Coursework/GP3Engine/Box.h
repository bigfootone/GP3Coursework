#ifndef _BOX_H
#define _BOX_H

#include "Common.h"
#include "Mesh.h"

struct Box
{
	vec3 boxPoints[6];
	vec3 center;
	float radius;

	void setPoints(MeshData* tempMesh)
	{
		vec3 min = vec3(0, 0, 0);
		vec3 max = vec3(0, 0, 0);
		for each (auto vertex in tempMesh->getVertives())
		{
			//find the max values
			if (vertex.position.x > max.x){ max.x = vertex.position.x; }
			if (vertex.position.y > max.y){ max.y = vertex.position.y; }
			if (vertex.position.z > max.z){ max.z = vertex.position.z; }
			//find the min values
			if (vertex.position.x < min.x){ min.x = vertex.position.x; }
			if (vertex.position.y < min.y){ min.y = vertex.position.y; }
			if (vertex.position.z < min.z){ min.z = vertex.position.z; }
		}

		boxPoints[0] = vec3(min.x, min.y, min.z);
		boxPoints[1] = vec3(max.x, min.y, min.z);
		boxPoints[2] = vec3(max.x, min.y, max.z);
		boxPoints[3] = vec3(min.x, min.y, max.z);
		boxPoints[4] = vec3(min.x, max.y, min.z);
		boxPoints[5] = vec3(max.x, max.y, min.z);
		boxPoints[6] = vec3(max.x, max.y, max.z);
		boxPoints[7] = vec3(min.x, max.y, max.z);

		center = vec3((min.x + max.x / 2), (min.y + max.y / 2), (min.z + max.z / 2));

		radius = max.x;
		if (max.y > radius)
		{
			radius = max.y;
		}
		if (max.z > radius)
		{
			radius = max.z;
		}

	}

	vec3 getPoints(int point)
	{
		return boxPoints[point];
	}

	vec3 getCenter()
	{
		return center;
	}

	void DrawBox(mat4 &modelMatrix)
	{
		glLineWidth(5);
		glColor4f(1, 0, 0, 0);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINE_LOOP);

		for each (vec3 P1 in boxPoints)
		{
			vec4 A = vec4(P1.x, P1.y, P1.z, 1) * modelMatrix;
			glVertex3f(A.x, A.y, A.z);
		}
		glEnd();
	}
};

#endif