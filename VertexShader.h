#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class VertexShader
{
public:
	VertexShader(RenderingSystem* system);
	~VertexShader();
	bool release();

private:
	bool init(const void* shader_byte_code, size_t byte_code_size);

private:
	ID3D11VertexShader* m_vertex_shader;
	RenderingSystem* m_renderingSystem = nullptr;

private:
	friend class RenderingSystem;
	friend class DeviceContext;
};

