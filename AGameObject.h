#pragma once
#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Vector3D.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "GraphicsEngine.h"

class PrimitiveManager;
class GraphicsEngine;

struct vertex
{
	Vector3D position;
	Vector3D color;
};

class AGameObject
{
public:
	virtual void* getVertexList() = 0;
	virtual void setVertexList() = 0;
	virtual UINT getVertexListSize() = 0;

private:
	friend class PrimitiveManager;
	friend class GraphicsEngine;
};

