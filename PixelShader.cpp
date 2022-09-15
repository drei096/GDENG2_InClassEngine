#include "PixelShader.h"
#include "GraphicsEngine.h"

PixelShader::PixelShader()
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
	if (FAILED(GraphicsEngine::GetInstance()->d3d11_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_pixel_shader)))
	{
		return false;
	}
	return true;
}
