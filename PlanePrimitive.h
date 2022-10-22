#pragma once
#include "CubePrimitive.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"


class PlanePrimitive : public CubePrimitive
{
public:
	PlanePrimitive(std::string name);
	~PlanePrimitive();

	void update(float deltaTime) override;
	void draw(int width, int height);
	void setVertexList();

private:
	//FOR ANIMATION PURPOSES
	float animationTicks = 0.0f;
};
