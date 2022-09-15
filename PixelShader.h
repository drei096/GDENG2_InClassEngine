#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class PixelShader
{
public:
	PixelShader();
	~PixelShader();
	bool release();

private:
	bool init(const void* shader_byte_code, size_t byte_code_size);

private:
	ID3D11PixelShader* m_pixel_shader;

private:
	friend class GraphicsEngine;
	friend class DeviceContext;



};

