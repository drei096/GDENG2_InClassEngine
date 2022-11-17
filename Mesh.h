#pragma once

#include "Resource.h"
#include "Prerequisites.h"


class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	VertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();
	VertexShader* getVertexShader();

private:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	VertexShader* vertexShader = nullptr;

private:
	friend class DeviceContext;
};

