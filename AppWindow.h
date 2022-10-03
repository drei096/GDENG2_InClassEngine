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

	void update();

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
	VertexBuffer* m_vertex_buffer;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	//CAMERA MATRIX
	Matrix4x4 m_world_cam;

	//MOUSE MOVE ROTATION VALUES
	float m_rot_x = 0;
	float m_rot_y = 0;
	float m_rot_z = 0;

	//KEY MOVE TRANSLATE VALUES
	float m_forward = 0.0f;
	float m_right = 0.0f;
	float m_up = 0.0f;

	//VALUES FOR FPS CAMERA
	bool isRMouseClicked = false;
	float camSpeed = 0.1f;
};

