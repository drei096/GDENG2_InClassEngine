#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"

struct vertex
{
	Vector3D position;
	Vector3D position1;
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
	Window::OnCreate();
	GraphicsEngine::GetInstance()->init();
	swapChain = GraphicsEngine::GetInstance()->createSwapChain();

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

	
	//quad green
	vertex list[]
	{
		{Vector3D(-0.5f, -0.5f, 0.0f),   Vector3D(-0.32f, -0.11f, 0.0f),            Vector3D(0,1,0),    Vector3D(1,1,0)  },
		{Vector3D(-0.5f, 0.5f, 0.0f),    Vector3D(-0.11f, 0.78f, 0.0f),            Vector3D(0,1,0),     Vector3D(1,0,1)},
		{Vector3D(0.5f, -0.5f, 0.0f),    Vector3D(0.75f, -0.73f, 0.0f),            Vector3D(0,1,0),    Vector3D(0,0,1)},
		{Vector3D(0.5f, 0.5f, 0.0f),	     Vector3D(0.88f, 0.77f, 0.0f),            Vector3D(0,1,0),    Vector3D(0,1,0)}
	};
	

	m_vertex_buffer = GraphicsEngine::GetInstance()->createVertexBuffer();
	UINT size_of_list = ARRAYSIZE(list);


	//CREATING PIXEL SHADER
	void* shader_byte_code = nullptr;
	UINT size_of_shader = 0;
	GraphicsEngine::GetInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_of_shader);
	m_ps = GraphicsEngine::GetInstance()->createPixelShader(shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();



	//CREATING VERTEX SHADER
	GraphicsEngine::GetInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_of_shader);
	m_vs = GraphicsEngine::GetInstance()->createVertexShader(shader_byte_code, size_of_shader);
	m_vertex_buffer->load(list, sizeof(vertex), size_of_list, shader_byte_code, size_of_shader);
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
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	

	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vertex_buffer->getSizeVertexList(), 0);


	swapChain->present(true);

	old_delta = new_delta;
	new_delta = ::GetTickCount();
	deltaTime = (old_delta) ? ((new_delta - old_delta) / 1000.0f) : 0;
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vertex_buffer->release();
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

	deltaScale += deltaTime / 0.15f;

	Matrix4x4 temp;


	cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(deltaScale) + 1.0f) / 2.0f));
	temp.setTranslationMatrix(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), deltaPos));

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
