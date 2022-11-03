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
	//PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, Vector3D(0.0f, 2.0f, 1.0f), ShaderTypes::LERPING_ALBEDO);
	//PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, 2.0f, 1.0f, 0.0f, ShaderTypes::LERPING_ALBEDO);
	//PrimitiveManager::GetInstance()->createObjectWithTransformations(PrimitiveManager::CUBE, ShaderTypes::LERPING_ALBEDO, Vector3D(1.0f, 2.0f, 0.0f), Vector3D(1.5f, 1.5f, 1.5f), Vector3D(0.0f, 45.0f, 10.0f));
	 
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	InputSystem::GetInstance()->update(m_hwnd);

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
	/*
	Vector4D D = Vector4D(-1.0f, 1.0f, 0.0f, 0.0f);

	float width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	float height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	Vector4D scale = Vector4D(width * 0.5f, -height * 0.5f, 1.0f - 0.0f, 1.0f);
	scale = Vector4D(1 / scale.x, 1 / scale.y, 1 / scale.z, 1 / scale.w);

	Vector4D offset = Vector4D(-0.0f, -0.0f, -0.0f, 0.0f);
	offset = Vector4D((scale.x * offset.x + D.x), (scale.y * offset.y + D.y), (scale.z * offset.z + D.z), (scale.w * offset.w + D.w));

	Matrix4x4 transform = ViewportCameraManager::getInstance()->getSceneCamera()->getMatrix().multiplyTo(ViewportCameraManager::getInstance()->getSceneCameraViewMatrix());
	transform = transform.multiplyTo(ViewportCameraManager::getInstance()->GetSceneCameraProjectionMatrix());
	transform.inverse();

	Vector4D result = Vector4D((mouse_pos.m_x * scale.x + offset.x), (mouse_pos.m_y * scale.y + offset.y), (0.0f * scale.z + offset.z), (1.0f * scale.w + offset.w));

	Vector4D Z = Vector4D(result.z, result.z, result.z, result.z);
	Vector4D Y = Vector4D(result.y, result.y, result.y, result.y);
	Vector4D X = Vector4D(result.x, result.x, result.x, result.x);
	Vector4D transformCoordResult = Vector4D((Z.x * transform.matrix[2][0] + transform.matrix[3][0]), (Z.y * transform.matrix[2][1] + transform.matrix[3][1]), (Z.z * transform.matrix[2][2] + transform.matrix[3][2]), (Z.w * transform.matrix[2][3] + transform.matrix[3][3]));
	transformCoordResult = Vector4D((Y.x * transform.matrix[1][0] + transformCoordResult.x), (Y.y * transform.matrix[1][1] + transformCoordResult.y), (Y.z * transform.matrix[1][2] + transformCoordResult.z), (Y.w * transform.matrix[1][3] + transformCoordResult.w));
	transformCoordResult = Vector4D((X.x * transform.matrix[0][0] + transformCoordResult.x), (X.y * transform.matrix[0][1] + transformCoordResult.y), (X.z * transform.matrix[0][2] + transformCoordResult.z), (X.w * transform.matrix[0][3] + transformCoordResult.w));
	Vector4D W = Vector4D(transformCoordResult.w, transformCoordResult.w, transformCoordResult.w, transformCoordResult.w);
	Vector4D xm_divide = Vector4D(transformCoordResult.x / W.x, transformCoordResult.y / W.y, transformCoordResult.z / W.z, transformCoordResult.w / W.w);

	PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, Vector3D(xm_divide.x, xm_divide.y, xm_divide.z), ShaderTypes::ALBEDO);

	std::cout << xm_divide.x << ", " << xm_divide.y << ", " << xm_divide.z << std::endl;
	*/


	
	Matrix4x4 viewMatrixInverse;
	Matrix4x4 projMatrix;
	Matrix4x4 viewProjMatrix;

	

	float width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	float height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;
	float aspectRatio = width / height;


	float vx = ((2.0f * mouse_pos.m_x / width ) - 1.0f);
	float vy = (1.0f - (2.0f * mouse_pos.m_y / height ));
	

	ray.origin = Vector4D(ViewportCameraManager::getInstance()->getSceneCamera()->getLocalPosition(), 1.0f);
	ray.direction = Vector4D(vx, vy, 1.0f, 1.0f);

	viewMatrixInverse = ViewportCameraManager::getInstance()->getSceneCameraViewMatrix();
	viewMatrixInverse.inverse();
	projMatrix = ViewportCameraManager::getInstance()->GetSceneCameraProjectionMatrix();

	ray.origin = viewMatrixInverse.multiplyTo(ray.origin);
	ray.direction = projMatrix.multiplyTo(ray.direction);
	ray.direction = viewMatrixInverse.multiplyTo(ray.direction);
	
	//ray.direction = Vector3D::getUnitVector(ray.direction);

	
	std::cout << ray.origin.x << ", " << ray.origin.y << ", " << ray.origin.z << std::endl;
	std::cout << ray.direction.x << ", " << ray.direction.y << ", " << ray.direction.z << std::endl;

	PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, Vector3D(ray.origin.x, ray.origin.y, ray.origin.z), ShaderTypes::ALBEDO);
	PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, Vector3D(ray.direction.x, ray.direction.y, ray.direction.z), ShaderTypes::ALBEDO);
	
	
	
	
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