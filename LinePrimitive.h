#pragma once
#include "DeviceContext.h"
#include "AGameObject.h"


class LinePrimitive : public AGameObject
{
public:
	LinePrimitive(std::string name, Vector3D origin, Vector3D line);
	void* getVertexList();
	UINT getVertexListSize();
	void setVertexList();

	void update(float deltaTime) override;
	void draw(float width, float height) override;


	VertexBuffer* getVertexBuffer();

	

};

