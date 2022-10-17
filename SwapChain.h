#pragma once
#include <d3d11.h>

class DeviceContext;
class SwapChain
{
public:
	SwapChain();
	~SwapChain();
	bool init(HWND hwnd, UINT width, UINT height);
	bool release();
	bool present(bool vsync);

private:
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;

private:
	friend class DeviceContext;
};

