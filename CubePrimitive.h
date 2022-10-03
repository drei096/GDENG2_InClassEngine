#pragma once
#include "AGameObject.h"

struct vertex;

class CubePrimitive : public AGameObject
{
public:
	CubePrimitive();

	void* getVertexList() override;
	UINT getVertexListSize() override;
	void setVertexList() override;

	void setIndexList();
	void* getIndexList();
	UINT getIndexListSize();

	VertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();

	PixelShader* m_ps;
	VertexShader* m_vs;

	bool release();

private:
	vertex vertex_list[8];
	unsigned int index_list[36];
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
};

