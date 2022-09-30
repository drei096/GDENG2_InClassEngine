#include "PrimitiveManager.h"

#include "DeviceContext.h"


PrimitiveManager* PrimitiveManager::GetInstance()
{
	static PrimitiveManager primitiveManager;
	return &primitiveManager;
}

void PrimitiveManager::initQuad(float posx, float posy, float posz, float r, float g, float b, void* shader_byte_code, size_t byte_code_size)
{
	auto newQuadPrimitive = new QuadPrimitive();
	newQuadPrimitive->setVertexList(posx, posy, posz, r,g,b);

	newQuadPrimitive->vertexBuffer = GraphicsEngine::GetInstance()->createVertexBuffer();
	UINT size_list = newQuadPrimitive->getVertexListSize();

	newQuadPrimitive->vertexBuffer->load(newQuadPrimitive->getVertexList(), sizeof(vertex), size_list, shader_byte_code, byte_code_size);

	quads.push_back(newQuadPrimitive);
}

void PrimitiveManager::DrawQuad()
{
	
}




