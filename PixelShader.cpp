#include "PixelShader.h"
#include "RenderingSystem.h"

PixelShader::PixelShader(RenderingSystem* system) : m_renderingSystem(system)
{
}

PixelShader::~PixelShader()
{
}

bool PixelShader::release()
{
	m_pixel_shader->Release();
	delete this;
	return true;
}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (FAILED(m_renderingSystem->d3d11_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_pixel_shader)))
	{
		return false;
	}
	return true;
}
