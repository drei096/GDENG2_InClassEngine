#pragma once
#include <d3d11.h>
#include "ShaderCollection.h"
#include "Prerequisites.h"

class VertexBuffer
{
public:
	VertexBuffer(RenderingSystem* system);
	~VertexBuffer();
	bool load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader, ShaderTypes shaderType);
	bool release();
	UINT getSizeVertexList();

private:
	UINT m_size_vertex;
	UINT m_size_list;
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_input_layout;
	RenderingSystem* m_renderingSystem = nullptr;

private:
	friend class DeviceContext;

};

