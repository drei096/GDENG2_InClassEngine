#include "AppWindow.h"
#include <Windows.h>
#include "EngineTime.h"

/*
struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};
*/

__declspec(align(16))
struct constant
{
	float m_angle;
};


AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::OnCreate()
{
	//CREATE WINDOW AND SWAP CHAIN
	Window::OnCreate();
	GraphicsEngine::GetInstance()->init();
	swapChain = GraphicsEngine::GetInstance()->createSwapChain();

	//GET RECT MEASUREMENTS AND INIT SWAPCHAIN
	RECT rc = this->getClientWindowRect();
	swapChain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	//CUBE NORMALIZED VERTEX COORDINATES WITH COLOR DATA
	/*
	vertex list[] =
	{
		//X - Y - Z
		{-0.1f,-0.1f,0.0f,       1,0,0,  }, // POS1
		{-0.1f,0.1f,0.0f,        1,0,0,  }, // POS2
		{ 0.1f,-0.1f,0.0f,       0,0,1,  },// POS2
		{ 0.1f,0.1f,0.0f,        1,1,1,  }
	};
	*/

	

	//CREATE VERTEX BUFFER
	//m_vertex_buffer = GraphicsEngine::GetInstance()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::GetInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);


	//CREATE VERTEX SHADER AND LOAD VERTEX BUFFER
	m_vs = GraphicsEngine::GetInstance()->createVertexShader(shader_byte_code, size_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();

	PrimitiveManager::GetInstance()->initQuad(0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, shader_byte_code, size_shader);

	//m_vertex_buffer->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);


	//CREATE PIXEL SHADER
	GraphicsEngine::GetInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::GetInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();

	//CREATE CONSTANT BUFFER
	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::GetInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain,1.0f, 1.0f, 1.0f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	/*
	 * OLD IMPLEMENTATION OF DELTA TIME
	 *
	unsigned long new_time = 0;
	if (old_delta)
		new_time = ::GetTickCount() - old_delta;
	deltaTime = new_time / 1000.0f;
	old_delta = ::GetTickCount();
	*
	*
	*/


	m_angle += 1.57f * EngineTime::getDeltaTime();
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::GetInstance()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);


	//SET THE VERTICES OF THE QUAD TO DRAW
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexBuffer(PrimitiveManager::GetInstance()->quads[0]->vertexBuffer);

	// FINALLY DRAW THE QUAD
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->drawTriangleStrip(PrimitiveManager::GetInstance()->quads[0]->vertexBuffer->getSizeVertexList(), 0);
	swapChain->present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	//m_vertex_buffer->release();
	swapChain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::GetInstance()->release();
}