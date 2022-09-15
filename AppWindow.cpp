#include "AppWindow.h"
#include <Windows.h>

struct vec3
{
	float x;
	float y;
	float z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
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
		{-0.5f, -0.5f, 0.0f,   -0.32f, -0.11f, 0.0f,            0,1,0,    1,1,0  },
		{-0.5f, 0.5f, 0.0f,    -0.11f, 0.78f, 0.0f,            0,1,0,     1,0,1},
		{0.5f, -0.5f, 0.0f,    0.75f, -0.73f, 0.0f,            0,1,0,    0,0,1},
		{0.5f, 0.5f, 0.0f,	     0.88f, 0.77f, 0.0f,            0,1,0,    0,1,0}
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

	//get ticks
	constant cc;
	cc.m_time = GetTickCount();
	m_cb->update(GraphicsEngine::GetInstance()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//set default shaders
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vertex_buffer->getSizeVertexList(), 0);


	swapChain->present(false);
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