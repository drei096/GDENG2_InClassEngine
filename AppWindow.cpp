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
	//CREATING THE WINDOW AND SWAP CHAIN
	Window::OnCreate();
	GraphicsEngine::GetInstance()->init();
	swapChain = GraphicsEngine::GetInstance()->createSwapChain();

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

	//clear render target
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 1, 1, 1, 1);

	//set viewport size of render target
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);



	
	updateQuadPos();


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

void AppWindow::updateQuadPos()
{
	//get ticks
	constant cc;
	cc.m_time = GetTickCount();

	deltaPos += deltaTime * 0.1f;
	if (deltaPos > 1.0f)
		deltaPos = 0;

	deltaScale += deltaTime /1.0f;

	Matrix4x4 temp;
	


	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(deltaScale) + 1.0f) / 2.0f));
	//temp.setTranslationMatrix(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), deltaPos));
	//cc.m_world *= temp;

	

	cc.m_world.setScale(Vector3D(1, 1, 1));

	temp.setIdentity();
	temp.setQuaternionRotation(deltaScale, 0, 1, 0);
	cc.m_world *= temp;

	

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);

	m_cb->update(GraphicsEngine::GetInstance()->getImmediateDeviceContext(), &cc);
	
}
