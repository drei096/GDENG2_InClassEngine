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

	//PrimitiveManager::GetInstance()->init();

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
	

	PrimitiveManager::GetInstance()->initQuad(0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, shader_byte_code, size_shader);

	//m_vertex_buffer->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();

	//CREATE PIXEL SHADER
	GraphicsEngine::GetInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::GetInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();



}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain,1.0f, 1.0f, 1.0f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


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
	PrimitiveManager::GetInstance()->release();
	swapChain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::GetInstance()->release();
}