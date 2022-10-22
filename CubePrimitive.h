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


	void update(float deltaTime) override;
	void draw(float width, float height) override;


	bool release() override;


	

protected:
	vertex vertex_list[8];
	unsigned int index_list[36];

private:
	//FOR ANIMATION PURPOSES
	float animationTicks = 0.0f;
	
};

