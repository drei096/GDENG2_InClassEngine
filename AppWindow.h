#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "PrimitiveManager.h"


class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;

	void updateQuadPos();

	/*
	virtual void OnFocus() override;
	virtual void OnKillFocus() override;

	

	//inherited from input listener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;
	*/

private:
	SwapChain* swapChain;
	//VertexBuffer* m_vertex_buffer;
	VertexShader* m_vs;
	PixelShader* m_ps;

	float old_delta;
	float new_delta;
	float deltaTime;

	float deltaScale;
	float deltaPos;

	float m_rot_x = 0;
	float m_rot_y = 0;
	float m_rot_z = 0;

	float m_scale_cube = 1;
	float m_angle = 0.0f;

};

