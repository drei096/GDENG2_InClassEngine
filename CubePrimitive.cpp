#include "CubePrimitive.h"

#include "DeviceContext.h"
#include "LinePrimitive.h"

CubePrimitive::CubePrimitive()
{
	setVertexList();
	setIndexList();
	setNormalsList();

	vertexBuffer = GraphicsEngine::GetInstance()->createVertexBuffer();

	

	indexBuffer = GraphicsEngine::GetInstance()->createIndexBuffer();
	indexBuffer->load(index_list, getIndexListSize());

	void* shader_byte_code = nullptr;
	UINT size_of_shader = 0;

	//CREATING VERTEX SHADER
	GraphicsEngine::GetInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_of_shader);
	m_vs = GraphicsEngine::GetInstance()->createVertexShader(shader_byte_code, size_of_shader);
	vertexBuffer->load(vertex_list, sizeof(vertex), getVertexListSize(), shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();

	//CREATING PIXEL SHADER
	GraphicsEngine::GetInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_of_shader);
	m_ps = GraphicsEngine::GetInstance()->createPixelShader(shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();

	//ADDED RASTERIZER STATE FOR WIREFRAME MODE
	initWireFrameRS();
	
}

void* CubePrimitive::getVertexList()
{
	return vertex_list;
}

UINT CubePrimitive::getVertexListSize()
{
	return ARRAYSIZE(vertex_list);
}

void CubePrimitive::setVertexList()
{
	//FRONT FACE OF CUBE
	vertex_list[0] = { Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0) };
	vertex_list[1] = { Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,0,1) };
	vertex_list[2] = { Vector3D(0.5f,0.5f,-0.5f),   Vector3D(0,1,0) };
	vertex_list[3] = { Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(0,0,1) };

	//BACK FACE OF CUBE
	vertex_list[4] = { Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0) };
	vertex_list[5] = { Vector3D(0.5f,0.5f,0.5f),    Vector3D(1,0,0) };
	vertex_list[6] = { Vector3D(-0.5f,0.5f,0.5f),   Vector3D(1,0,1) };
	vertex_list[7] = { Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,1) };
}

void CubePrimitive::setIndexList()
{
	//CREATING INDEX BUFFER
	unsigned int cube_index_list[] =
	{
		//FRONT SIDE OF CUBE
		0,1,2,
		2,3,0,

		//BACK SIDE OF CUBE
		4,5,6,
		6,7,4,

		//TOP SIDE OF CUBE
		1,6,5,
		5,2,1,

		//BOTTOM SIDE OF CUBE
		7,0,3,
		3,4,7,

		//RIGHT SIDE OF CUBE
		3,2,5,
		5,4,3,

		//LEFT SIDE OF CUBE
		7,6,1,
		1,0,7
	};

	for(int i = 0; i < 36; i++)
	{
		index_list[i] = cube_index_list[i];
	}
}

void* CubePrimitive::getIndexList()
{
	return index_list;
}

UINT CubePrimitive::getIndexListSize()
{
	return ARRAYSIZE(index_list);
}

VertexBuffer* CubePrimitive::getVertexBuffer()
{
	return this->vertexBuffer;
}

IndexBuffer* CubePrimitive::getIndexBuffer()
{
	return this->indexBuffer;
}

void CubePrimitive::setNormalsList()
{
	int indexListIterator = 0;

	for(int i = 0; i < 12; i++)
	{
		normalsList[i] = Vector3D::getSurfaceNormal(vertex_list[index_list[indexListIterator]].position, vertex_list[index_list[indexListIterator + 1]].position, vertex_list[index_list[indexListIterator + 2]].position);
		indexListIterator += 3;
	}
}

void* CubePrimitive::getNormalsList()
{
	return normalsList;
}

UINT CubePrimitive::getNormalsListSize()
{
	return ARRAYSIZE(normalsList);
}

void CubePrimitive::drawNormalLines(ConstantBuffer* m_cb)
{
	LinePrimitive* newLine;

	for(int i = 0; i < getNormalsListSize(); i+=2)
	{
		newLine = new LinePrimitive(normalsList[i]);

		GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(newLine->m_vs, m_cb);
		GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(newLine->m_ps, m_cb);

		//set default shaders
		GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexShader(newLine->m_vs);
		GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setPixelShader(newLine->m_ps);

		//set the vertices of the object/cube/triangle to draw
		GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexBuffer(newLine->getVertexBuffer());


		//draw the line
		GraphicsEngine::GetInstance()->getImmediateDeviceContext()->drawLineList(2, 0);
	}

	
}

bool CubePrimitive::release()
{
	if (vertexBuffer->release() && indexBuffer->release())
		return true;
	else
		return false;
}

//ADDED RASTERIZER STATE FOR WIREFRAME MODE
void CubePrimitive::initWireFrameRS()
{
	D3D11_RASTERIZER_DESC wfd;
	ZeroMemory(&wfd, sizeof(D3D11_RASTERIZER_DESC));
	wfd.FillMode = D3D11_FILL_WIREFRAME;
	wfd.CullMode = D3D11_CULL_NONE;
	wfd.DepthClipEnable = true;

	GraphicsEngine::GetInstance()->d3d11_device->CreateRasterizerState(&wfd, &mWireFrameRS);

}
