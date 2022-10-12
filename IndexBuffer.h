#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(RenderingSystem* system);
	~IndexBuffer();
	bool load(void* list_indices, UINT size_list);
	bool release();
	UINT getSizeIndexList();

private:
	UINT m_size_list;
	ID3D11Buffer* m_buffer;
	RenderingSystem* m_renderingSystem = nullptr;

private:
	friend class DeviceContext;

};

