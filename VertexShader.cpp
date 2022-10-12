#include "VertexShader.h"
#include "RenderingSystem.h"

VertexShader::VertexShader(RenderingSystem* system) : m_renderingSystem(system)
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
	if(FAILED(m_renderingSystem->d3d11_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vertex_shader)))
	{
		return false;
	}
	return true;
}
