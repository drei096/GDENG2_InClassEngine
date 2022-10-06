#include "LinePrimitive.h"

LinePrimitive::LinePrimitive(Vector3D line)
{
	vertex vertex_list[] =
	{
		{Vector3D(0.0f, 0.0f, 0.0f), Vector3D(1,0,0)},
		{line, Vector3D(1,0,0)}
	};

	vertexBuffer = GraphicsEngine::GetInstance()->createVertexBuffer();


	void* shader_byte_code = nullptr;
	UINT size_of_shader = 0;

	//CREATING VERTEX SHADER
	GraphicsEngine::GetInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_of_shader);
	m_vs = GraphicsEngine::GetInstance()->createVertexShader(shader_byte_code, size_of_shader);
	vertexBuffer->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();

	//CREATING PIXEL SHADER
	GraphicsEngine::GetInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_of_shader);
	m_ps = GraphicsEngine::GetInstance()->createPixelShader(shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();
}

void* LinePrimitive::getVertexList()
{
	return nullptr;
}

UINT LinePrimitive::getVertexListSize()
{
	return 0;
}

void LinePrimitive::setVertexList()
{
}



VertexBuffer* LinePrimitive::getVertexBuffer()
{
	return this->vertexBuffer;
}
