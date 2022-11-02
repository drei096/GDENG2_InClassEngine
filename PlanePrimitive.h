#pragma once
#include "CubePrimitive.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"


class PlanePrimitive : public CubePrimitive
{
public:
	PlanePrimitive(std::string name, ShaderTypes shaderType);
	~PlanePrimitive();

	void setVertexList(ShaderTypes shaderType);

	void update(float deltaTime) override;
	

private:
	//FOR ANIMATION PURPOSES
	float animationTicks = 0.0f;
};
