#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "Texture.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext, RenderingSystem* system);
	~DeviceContext();
	bool release();

	void clearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a);

	void setVertexBuffer(VertexBuffer* vertex_buffer);

	
	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

	void setTexture(VertexShader* vertex_shader, Texture* texture);
	void setTexture(PixelShader* pixel_shader, Texture* texture);

	void setIndexBuffer(IndexBuffer* index_buffer);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawLineList(UINT vertex_count, UINT start_vertex);

	void setViewportSize(UINT width, UINT height);

	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);



private:
	ID3D11DeviceContext* m_device_context;
	RenderingSystem* m_renderingSystem = nullptr;

private:
	friend class ConstantBuffer;
};

