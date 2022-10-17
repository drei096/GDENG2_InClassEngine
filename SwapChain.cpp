#include "SwapChain.h"
#include "RenderingSystem.h"

SwapChain::SwapChain(RenderingSystem* system) : m_renderingSystem(system)
{
	
}


SwapChain::~SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* deviceRef = m_renderingSystem->d3d11_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT res = m_renderingSystem->dxgiFactory->CreateSwapChain(deviceRef, &desc, &swapChain);
	if(FAILED(res))
	{
		return false;
	}

	ID3D11Texture2D* buffer = NULL;
	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(res))
	{
		return false;
	}

	res = deviceRef->CreateRenderTargetView(buffer, NULL, &renderTargetView);
	buffer->Release();
	if (FAILED(res))
	{
		return false;
	}

	//CREATING A DEPTH/STENCIL BUFFER
	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = width;
	tex_desc.Height = height;
	tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex_desc.MipLevels = 1;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.MiscFlags = 0;
	tex_desc.ArraySize = 1;
	tex_desc.CPUAccessFlags = 0;
	res = deviceRef->CreateTexture2D(&tex_desc, nullptr, &buffer);
	if (FAILED(res))
	{
		return false;
	}

	res = deviceRef->CreateDepthStencilView(buffer, NULL, &depthStencilView);
	buffer->Release();
	if (FAILED(res))
	{
		return false;
	}


	return true;
}

bool SwapChain::release()
{
	swapChain->Release();
	delete this;
	return true;
}

bool SwapChain::present(bool vsync)
{
	swapChain->Present(vsync, NULL);
	return true;
}
