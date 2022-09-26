#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};


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
	swapChain = GraphicsEngine::GetInstance()->createSwapChain();

	//INITIALIZE WORLD CAM MATRIX
	m_world_cam.setTranslationMatrix(Vector3D(0, 0, -2));

	//GETTING THE RECT OF WINDOW
	RECT rc = this->getClientWindowRect();
	swapChain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	/*
	//quad rainbow
	vertex list[] =
	{
		{-0.5f, -0.5f, 0.0f, 1,0,0},
		{-0.5f, 0.5f, 0.0f, 0,1,0},
		{0.5f, -0.5f, 0.0f, 0,0,1},
		{0.5f, 0.5f, 0.0f,1,1,0},
	};
	*/

	/*
	//triangle rainbow
	vertex list[]
	{
		{-0.5f, -0.5f, 0.0f,1,0,0}, 
		{0.0f, 0.5f, 0.0f,0,1,0}, 
		{0.5f, -0.5f, 0.0f,0,0,1}, 
	};
	*/

	
	//cube
	vertex vertex_list[]
	{
		//FRONT FACE OF CUBE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE OF CUBE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }
	};
	
	//CREATING VERTEX BUFFER
	m_vertex_buffer = GraphicsEngine::GetInstance()->createVertexBuffer();
	UINT size_of_list = ARRAYSIZE(vertex_list);


	//CREATING INDEX BUFFER
	unsigned int index_list[] =
	{
		//FRONT SIDE OF CUBE
		0,1,2,
		2,3,0,

		//BACK SIDE OF CUBE
		4,5,6,
		6,7,4,

		//TOP SIDE OF CUBE
		1,6,5,
		5,2,1,

		//BOTTOM SIDE OF CUBE
		7,0,3,
		3,4,7,

		//RIGHT SIDE OF CUBE
		3,2,5,
		5,4,3,

		//LEFT SIDE OF CUBE
		7,6,1,
		1,0,7
	};
	m_ib = GraphicsEngine::GetInstance()->createIndexBuffer();
	UINT size_of_index_list = ARRAYSIZE(index_list);
	m_ib->load(index_list, size_of_index_list);

	//CREATING PIXEL SHADER
	void* shader_byte_code = nullptr;
	UINT size_of_shader = 0;
	GraphicsEngine::GetInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_of_shader);
	m_ps = GraphicsEngine::GetInstance()->createPixelShader(shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();



	//CREATING VERTEX SHADER
	GraphicsEngine::GetInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_of_shader);
	m_vs = GraphicsEngine::GetInstance()->createVertexShader(shader_byte_code, size_of_shader);
	m_vertex_buffer->load(vertex_list, sizeof(vertex), size_of_list, shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();


	//CREATING CONSTANT BUFFER
	constant cc;
	cc.m_time = 0;
	m_cb = GraphicsEngine::GetInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	InputSystem::GetInstance()->update();

	//clear render target
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 1, 1, 1, 1);

	//set viewport size of render target
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);



	
	update();


	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//set default shaders
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//set the vertices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	//set the indices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);


	swapChain->present(true);

	old_delta = new_delta;
	new_delta = ::GetTickCount();
	deltaTime = (old_delta) ? ((new_delta - old_delta) / 1000.0f) : 0;
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vertex_buffer->release();
	m_ib->release();
	m_cb->release();
	swapChain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::GetInstance()->release();

}

void AppWindow::update()
{
	//get ticks
	constant cc;
	cc.m_time = GetTickCount();

	deltaPos += deltaTime * 0.1f;
	if (deltaPos > 1.0f)
		deltaPos = 0;

	deltaScale += deltaTime /1.0f;

	Matrix4x4 temp;
	Matrix4x4 world_cam;

	cc.m_world.setIdentity();
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setQuaternionRotation(m_rot_x, 1, 0, 0);
	world_cam *= temp;

	temp.setIdentity();
	temp.setQuaternionRotation(m_rot_y, 0, 1, 0);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.3f);
	new_pos = new_pos + world_cam.getXDirection() * (m_right * 0.3f);

	world_cam.setTranslationMatrix(new_pos);

	m_world_cam = world_cam;
	world_cam.inverse();




	cc.m_view = world_cam;
	/*cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);*/

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	cc.m_proj.setPerspectiveFOVLH(1.57f, (float)width / (float)height, 0.1f, 100.0f);

	m_cb->update(GraphicsEngine::GetInstance()->getImmediateDeviceContext(), &cc);
	
}

void AppWindow::onKeyDown(int key)
{

	/*
	 *MOVE CUBE TEST
	switch(key)
	{
	case 'A':
		m_rot_y += 0.707f * deltaTime;
		break;
	case 'D':
		m_rot_y -= 0.707f * deltaTime;
		break;
	}
	*/

	//MOVE CAMERA TEST
	switch(key)
	{
	case 'W':
		m_forward = 1.0f;
		break;

	case 'S':
		m_forward = -1.0f;
		break;

	case 'A':
		m_right = -1.0f;
		break;

	case 'D':
		m_right = 1.0f;
		break;
	}
}

void AppWindow::onKeyUp(int key)
{
	//MOVE CAMERA TEST
	m_forward = 0.0f;
	m_right = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_rot_x -= (mouse_pos.m_y - (height / 2.0f)) * deltaTime;
	m_rot_y -= (mouse_pos.m_x - (width / 2.0f)) * deltaTime;

	

	InputSystem::GetInstance()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
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
