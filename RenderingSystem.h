#pragma once
#include<d3d11.h>
#include "Prerequisites.h"



class RenderingSystem
{
public:
	RenderingSystem();
	bool init();
	bool release();
	~RenderingSystem();

	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();

	VertexBuffer* createVertexBuffer();
	ConstantBuffer* createConstantBuffer();
	IndexBuffer* createIndexBuffer();

	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();

	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

	ID3D11Device* getD3D11Device();
	ID3D11DeviceContext* getD3D11DeviceContext();

private:
	ID3D11Device* d3d11_device;
	D3D_FEATURE_LEVEL featureLevel;
	IDXGIDevice* dxgiDevice;
	IDXGIAdapter* dxgiAdapter;
	IDXGIFactory* dxgiFactory;
	DeviceContext* imm_deviceContext;
	ID3D11DeviceContext* imm_Context;

	ID3DBlob* m_blob = nullptr;


	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;


	



private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
	friend class IndexBuffer;
};


