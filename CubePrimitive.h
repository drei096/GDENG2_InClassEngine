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

	void setNormalsList();
	void* getNormalsList();
	UINT getNormalsListSize();

	PixelShader* m_ps;
	VertexShader* m_vs;

	//ADDED RASTERIZER STATE FOR WIREFRAME MODE
	ID3D11RasterizerState* mWireFrameRS;

	//ADDED FOR DRAWING NORMALS LINES
	void drawNormalLines(ConstantBuffer* m_cb);

	bool release();

private:
	vertex vertex_list[8];
	unsigned int index_list[36];

	Vector3D normalsList[12];

	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;

	

private:
	//ADDED RASTERIZER STATE FOR WIREFRAME MODE
	void initWireFrameRS();
};

