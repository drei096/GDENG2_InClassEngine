#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"


class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;

	void updateQuadPos();

	

private:
	SwapChain* swapChain;
	VertexBuffer* m_vertex_buffer;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;


	float deltaScale;
	float deltaPos;

	float m_rot_x = 0;
	float m_rot_y = 0;
	float m_rot_z = 0;

	float m_scale_cube = 1;
	float m_angle = 0.0f;

	float animationTicks = 0.0f;
	bool isForwardTime = true;
};

