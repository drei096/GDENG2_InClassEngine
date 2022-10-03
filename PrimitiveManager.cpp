#include "PrimitiveManager.h"


PrimitiveManager* PrimitiveManager::GetInstance()
{
	static PrimitiveManager primitiveManager;
	return &primitiveManager;
}

void PrimitiveManager::init()
{
}

void PrimitiveManager::initQuad(float posx, float posy, float posz, float r, float g, float b, float offsetX, float offsetY, void* shader_byte_code, size_t byte_code_size)
{
	/*
	auto newQuadPrimitive = new QuadPrimitive();
	newQuadPrimitive->setVertexList(posx, posy, posz, r, g, b, offsetX, offsetY);

	newQuadPrimitive->vertexBuffer = GraphicsEngine::GetInstance()->createVertexBuffer();
	UINT size_list = newQuadPrimitive->getVertexListSize();

	newQuadPrimitive->vertexBuffer->load(newQuadPrimitive->getVertexList(), sizeof(vertex), size_list, shader_byte_code, byte_code_size);

	quads.push_back(newQuadPrimitive);
	*/
}

void PrimitiveManager::DrawQuad()
{

}

void PrimitiveManager::DrawCube(ConstantBuffer* m_cb)
{
	auto newCube = new CubePrimitive();

	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(newCube->m_vs, m_cb);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(newCube->m_ps, m_cb);

	//set default shaders
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexShader(newCube->m_vs);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setPixelShader(newCube->m_ps);

	//set the vertices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexBuffer(newCube->getVertexBuffer());

	//set the indices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setIndexBuffer(newCube->getIndexBuffer());

	//draw the cube
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(newCube->getIndexListSize(), 0, 0);
}

void PrimitiveManager::release()
{
	/*
	std::vector<QuadPrimitive*>::iterator i;
	for (i = quads.begin(); i != quads.end(); ++i)
	{
		static_cast<QuadPrimitive*>(*i)->release();
		delete* i;
	}
	quads.clear();
	*/
}

/*
void PrimitiveManager::init()
{
	vertexBuffer = GraphicsEngine::GetInstance()->createVertexBuffer();
}
*/
