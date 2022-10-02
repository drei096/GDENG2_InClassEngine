#pragma once
#include <vector>
#include "VertexBuffer.h"

class PrimitiveManager;

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

class AGameObject
{
protected:
	

	

public:
	virtual void* getVertexList() = 0;
	virtual void setVertexList(float posx, float posy, float posz, float r, float g, float b, float offsetX, float offsetY) = 0;
	virtual UINT getVertexListSize() = 0;

private:
	friend class PrimitiveManager;
};

