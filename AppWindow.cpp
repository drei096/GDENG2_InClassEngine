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

	InitIMGUI();

	//CREATING A CUBE OBJECT
	
	PrimitiveManager::GetInstance()->createObject(PrimitiveManager::CUBE, ShaderTypes::ALBEDO);
	PrimitiveManager::GetInstance()->createObject(PrimitiveManager::PLANE, ShaderTypes::ALBEDO);
	//PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, Vector3D(0.0f, 2.0f, 1.0f), ShaderTypes::LERPING_ALBEDO);
	//PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, 2.0f, 1.0f, 0.0f, ShaderTypes::LERPING_ALBEDO);
	PrimitiveManager::GetInstance()->createObjectWithTransformations(PrimitiveManager::CUBE, ShaderTypes::ALBEDO, Vector3D(1.0f, 2.0f, 0.0f), Vector3D(1.5f, 1.5f, 1.5f), Vector3D(0.0f, 45.0f, 10.0f));

	
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


	PresentIMGUI();

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
	bool isFirstObjectFound = false;
	int listIterator = 0;
	const PrimitiveManager::List gameObjectList = PrimitiveManager::GetInstance()->getAllObjects();
	if (gameObjectList.empty())
		return;

	
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
	
	//ray.direction = Vector4D::getUnitVector(ray.direction);

	Vector3D temp;
	while(isFirstObjectFound == false)
	{
		float directionMagnitude = temp.getMagnitude(Vector3D(ray.direction.x, ray.direction.y, ray.direction.z));
		if (directionMagnitude < gameObjectList[listIterator]->getBoundingSphereValue())
		{
			std::cout << gameObjectList[listIterator]->getName() << std::endl;
			isFirstObjectFound = true;
		}
		else
			listIterator++;
	}

	//std::cout << temp.getMagnitude(Vector3D(ray.direction.x, ray.direction.y, ray.direction.z)) << std::endl;

	
	Vector3D rayOrigin3D = Vector3D(ray.origin.x, ray.origin.y, ray.origin.z);
	Vector3D rayDirection3D = Vector3D(ray.direction.x, ray.direction.y, ray.direction.z);

	for(int i = 0; i < gameObjectList.size(); i++)
	{
		Vector3D rayClosestPoint = rayOrigin3D + (rayDirection3D * (temp.dotProd((gameObjectList[i]->getLocalPosition() - rayOrigin3D), rayDirection3D) / temp.dotProd(rayDirection3D, rayDirection3D)));

		//get magnitude of rayclosestpoint
		float closestPointMagnitude = temp.getMagnitude(rayClosestPoint);
		//std::cout << closestPointMagnitude << std::endl;

		//finally, check to see if the distance is less than the current object's bounding sphere
		if(closestPointMagnitude < gameObjectList[i]->getBoundingSphereValue())
		{
			std::cout << gameObjectList[i]->getName() << std::endl;
			break;
		}

		//PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, rayClosestPoint, ShaderTypes::ALBEDO);
	}
	*/

	//PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, Vector3D(ray.origin.x, ray.origin.y, ray.origin.z), ShaderTypes::ALBEDO);
	//PrimitiveManager::GetInstance()->createObjectAtPoint(PrimitiveManager::CUBE, Vector3D(ray.direction.x, ray.direction.y, ray.direction.z), ShaderTypes::ALBEDO);
	
	
	
	
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

void AppWindow::InitIMGUI()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::GetInstance()->getRenderingSystem()->d3d11_device, GraphicsEngine::GetInstance()->getRenderingSystem()->imm_Context);
	ImGui::StyleColorsDark();
}

void AppWindow::PresentIMGUI()
{
	//START IMGUI FRAME
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//DRAW HERE
	ImGui::Begin("Credits");
	ImGui::Text("GDENG-2_InClassEngine v0.1\n");
	ImGui::Text("Created by Aldrey D. Gaurana - GDENG-2 X22\n");
	ImGui::Text("Acknowledgements:\n");
	ImGui::Text(" - Sir Del Gallego for the course\n");
	ImGui::Text(" - PardCode (https://www.youtube.com/c/PardCode)\n");
	ImGui::Text(" - RedBull (https://www.redbull.com/ph-en/)\n");
	ImGui::Text(" - Google (https://google.com)\n");
	ImGui::Text(" - Stack Overflow (https://stackoverflow.com)\n");
	ImGui::Text(" - IMGUI (https://github.com/ocornut/imgui)");

	ImGui::End();
	//DO NOT DRAW PAST HERE


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
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