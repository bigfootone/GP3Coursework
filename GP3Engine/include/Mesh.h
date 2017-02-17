#ifndef _MESH_H
#define _MESH_H

#include "Vertex.h"
#include "Common.h"

struct MeshData
{
	vector<Vertex> vertices;
	vector<int> indices;

	int getNumVerts()
	{
		return (int)vertices.size();
	};

	int getNumIndices()
	{
		return (int)indices.size();
	};

	vector<Vertex> getVertives()
	{
		return vertices;
	}
};

#endif