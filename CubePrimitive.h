#pragma once
#include "AGameObject.h"
#include "ShaderCollection.h"


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

	void setMesh(const wchar_t* mesh_path);
	void setTexture(const wchar_t* tex_path);

	

protected:
	flatColorVertex vertex_list[8];
	texturedVertex texd_vertex_list[24];
	unsigned int index_list[36];
	unsigned int texd_index_list[36];

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

