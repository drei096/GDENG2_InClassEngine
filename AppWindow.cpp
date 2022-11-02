#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "EngineTime.h"
#include "PrimitiveManager.h"
#include "ViewportCameraManager.h"


AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::OnCreate()
{
	//CREATING THE WINDOW, SWAP CHAIN, AND INPUT LISTENERS
	Window::OnCreate();
	InputSystem::GetInstance()->addListener(this);
	GraphicsEngine::GetInstance()->init();
	swapChain = GraphicsEngine::GetInstance()->getRenderingSystem()->createSwapChain();
	ShaderCollection::GetInstance()->LoadAllShaders();

	//GETTING THE RECT OF WINDOW AND INITIALIZING CAMERA
	RECT rc = this->getClientWindowRect();
	swapChain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	this->windowWidth = rc.right - rc.left;
	this->windowHeight = rc.bottom - rc.top;
	ViewportCameraManager::init();

	//CREATING A CUBE OBJECT
	
	PrimitiveManager::GetInstance()->createObject(PrimitiveManager::CUBE, ShaderTypes::ALBEDO);
	PrimitiveManager::GetInstance()->createObject(PrimitiveManager::PLANE, ShaderTypes::ALBEDO);
	PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, Vector3D(0.0f, 2.0f, 1.0f), ShaderTypes::LERPING_ALBEDO);
	//PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, 2.0f, 1.0f, 0.0f, ShaderTypes::LERPING_ALBEDO);
	//PrimitiveManager::GetInstance()->createObjectWithTransformations(PrimitiveManager::CUBE, ShaderTypes::LERPING_ALBEDO, Vector3D(1.0f, 2.0f, 0.0f), Vector3D(1.5f, 1.5f, 1.5f), Vector3D(0.0f, 45.0f, 10.0f));
	 
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	InputSystem::GetInstance()->update();

	//clear render target
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 0.1f, 0.1f, 0.2f, 1);

	//set viewport size of render target
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	ViewportCameraManager::getInstance()->update();


	PrimitiveManager::GetInstance()->renderAll(windowWidth, windowHeight);
	PrimitiveManager::GetInstance()->updateAll();

	swapChain->present(true);

	
}

void AppWindow::OnDestroy()
{
	//destroy primitives
	PrimitiveManager::GetInstance()->destroy();

	//destroy cam
	ViewportCameraManager::getInstance()->destroy();

	
	swapChain->release();
	GraphicsEngine::GetInstance()->release();

	Window::OnDestroy();
}



void AppWindow::onKeyDown(int key)
{
	
	
	
}

void AppWindow::onKeyUp(int key)
{
	
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	
}

void AppWindow::OnFocus()
{
	InputSystem::GetInstance()->addListener(this);
}

void AppWindow::OnKillFocus()
{
	InputSystem::GetInstance()->removeListener(this);
}






/*cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);*/