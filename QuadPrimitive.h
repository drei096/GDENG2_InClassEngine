#pragma once
#include "AGameObject.h"

struct vertex;

class QuadPrimitive : public AGameObject
{
public:
	QuadPrimitive();
	void setVertexList(float posx, float posy, float posz, float r, float g, float b) override;
	void* getVertexList() override;
	UINT getVertexListSize() override;

	VertexBuffer* vertexBuffer;

	bool release();

private:
	vertex list[4];
	
};