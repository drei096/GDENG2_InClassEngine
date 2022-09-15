#include "VertexShader.h"
#include "GraphicsEngine.h"

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

bool VertexShader::release()
{
	m_vertex_shader->Release();
	delete this;
	return true;
}

bool VertexShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if(FAILED(GraphicsEngine::GetInstance()->d3d11_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vertex_shader)))
	{
		return false;
	}
	return true;
}
