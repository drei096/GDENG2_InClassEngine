#pragma once
#include "AGameObject.h"
#include "ShaderCollection.h"
#include "MathUtils.h"


struct vertex;

class CubePrimitive : public AGameObject
{
public:
	CubePrimitive(std::string name, ShaderTypes shaderType);

	void* getVertexList();
	UINT getVertexListSize();
	void setVertexList(ShaderTypes shaderType);

	void setIndexList();
	void* getIndexList();
	UINT getIndexListSize();

	VertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();

	ConstantBuffer* getConstantBuffer();
	void* getCBData();

	void AssignVertexAndPixelShaders(ShaderTypes shaderType);


	void update(float deltaTime) override;
	void draw(float width, float height) override;


	void computeBoundingSphere();

	bool release() override;


	

protected:
	vertex vertex_list[8];
	unsigned int index_list[36];

private:
	//FOR ANIMATION PURPOSES
	float animationTicks = 0.0f;
	float scaleSpeed = 0.0f;
	float translateSpeed = 0.0f;

protected:
	LPCWSTR vertexShaderFile = L"";
	LPCWSTR pixelShaderFile = L"";
	ShaderTypes cubeShaderType;

	
};

