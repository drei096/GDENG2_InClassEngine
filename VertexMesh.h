#pragma once
#include <cmath>
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
public:
	VertexMesh() : position(), texcoord()
	{
	}

	VertexMesh(Vector3D position, Vector2D texcoord) : position(position), texcoord(texcoord)
	{
	}

	VertexMesh(const VertexMesh& vertex) : position(vertex.position), texcoord(vertex.texcoord)
	{
	}

	~VertexMesh()
	{

	}


public:
	Vector3D position;
	Vector2D texcoord;
};

