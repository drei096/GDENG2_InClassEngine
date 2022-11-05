#include "RenderingSystem.h"

#include "RenderingSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"

#include <d3dcompiler.h>




RenderingSystem::RenderingSystem()
{
}

bool RenderingSystem::init()
{
	HRESULT res = 0;

	D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_REFERENCE };
	UINT driverTypesCount = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	UINT featureLevelCount = ARRAYSIZE(featureLevels);

	for (UINT driverTypeIndex = 0; driverTypeIndex < driverTypesCount; driverTypeIndex++)
	{
		res = D3D11CreateDevice(NULL, driverTypes[driverTypeIndex], NULL, NULL, featureLevels, featureLevelCount, D3D11_SDK_VERSION, &d3d11_device, &featureLevel, &imm_Context);

		if (SUCCEEDED(res))
		{
			break;
		}
	}

	if (FAILED(res))
	{
		return false;
	}

	imm_deviceContext = new DeviceContext(imm_Context, this);

	d3d11_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);


	return true;
}

bool RenderingSystem::release()
{
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	imm_deviceContext->release();
	d3d11_device->Release();


	return true;
}

RenderingSystem::~RenderingSystem()
{
}

	

SwapChain* RenderingSystem::createSwapChain()
{

	return new SwapChain(this);
}

DeviceContext* RenderingSystem::getImmediateDeviceContext()
{
	return this->imm_deviceContext;
}

VertexBuffer* RenderingSystem::createVertexBuffer()
{
	return new VertexBuffer(this);
}

ConstantBuffer* RenderingSystem::createConstantBuffer()
{
	return new ConstantBuffer(this);
}

IndexBuffer* RenderingSystem::createIndexBuffer()
{
	return new IndexBuffer(this);
}


VertexShader* RenderingSystem::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader(this);
	if (!vs->init(shader_byte_code, byte_code_size))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

bool RenderingSystem::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* err_blob = nullptr;
	if (FAILED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &err_blob)))
	{
		if (err_blob) err_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void RenderingSystem::releaseCompiledShader()
{
	if (m_blob)m_blob->Release();
}

PixelShader* RenderingSystem::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader(this);
	if (!ps->init(shader_byte_code, byte_code_size))
	{
		ps->release();
		return nullptr;
	}

	return ps;
}

bool RenderingSystem::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* err_blob = nullptr;
	if (FAILED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &err_blob)))
	{
		if (err_blob) err_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

ID3D11Device* RenderingSystem::getD3D11Device()
{
	return d3d11_device;
}

ID3D11DeviceContext* RenderingSystem::getD3D11DeviceContext()
{
	return imm_Context;
}
