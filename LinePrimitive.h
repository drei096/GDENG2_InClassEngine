#pragma once
#include "DeviceContext.h"
#include "AGameObject.h"

class LinePrimitive : public AGameObject
{
public:
	LinePrimitive(Vector3D line);
	void* getVertexList() override;
	UINT getVertexListSize() override;
	void setVertexList() override;
	

	VertexBuffer* getVertexBuffer();
	
	PixelShader* m_ps;
	VertexShader* m_vs;


	bool release();

private:
	
	
	VertexBuffer* vertexBuffer = nullptr;


};

