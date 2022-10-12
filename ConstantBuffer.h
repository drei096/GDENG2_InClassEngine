#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class ConstantBuffer
{
public:
	ConstantBuffer(RenderingSystem* system);
	~ConstantBuffer();
	bool load(void* buffer, UINT size_buffer);
	bool release();
	void update(DeviceContext* context, void* buffer);

private:
	ID3D11Buffer* m_buffer;
	RenderingSystem* m_renderingSystem = nullptr;

private:
	friend class DeviceContext;

};

