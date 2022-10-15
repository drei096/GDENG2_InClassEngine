#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class SwapChain
{
public:
	SwapChain(RenderingSystem* system);
	~SwapChain();
	bool init(HWND hwnd, UINT width, UINT height);
	bool release();
	bool present(bool vsync);

private:
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;


	ID3D11DepthStencilView* depthStencilView = nullptr;


	RenderingSystem* m_renderingSystem = nullptr;

private:
	friend class DeviceContext;
};

