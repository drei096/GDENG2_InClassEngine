#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "Matrix4x4.h"
#include "ShaderCollection.h"
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "UIManager.h"


struct PickingRay
{
	Vector4D origin;
	Vector4D direction;
};


class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnFocus() override;
	virtual void OnKillFocus() override;

	//inherited from input listener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;


private:
	SwapChain* swapChain;
	

	float windowWidth = 0.0f;
	float windowHeight = 0.0f;

	PickingRay ray;


	
};

