#pragma once
#include "AGameObject.h"

struct vertex;

class CubePrimitive : public AGameObject
{
public:
	CubePrimitive(std::string name);

	void* getVertexList();
	UINT getVertexListSize();
	void setVertexList();

	void setIndexList();
	void* getIndexList();
	UINT getIndexListSize();

	VertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();

	ConstantBuffer* getConstantBuffer();
	void* getCBData();

	PixelShader* m_ps;
	VertexShader* m_vs;

	void update(float deltaTime) override;
	void draw(float width, float height) override;


	bool release();


	

protected:
	vertex vertex_list[8];
	unsigned int index_list[36];
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	ConstantBuffer* m_cb = nullptr;

	constantData cc;
};

