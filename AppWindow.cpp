
#include "AppWindow.h"
#include <Windows.h>
#include "EngineTime.h"

struct vec3
{
	float x, y, z;
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
	Window::OnCreate();
	GraphicsEngine::GetInstance()->init();
	swapChain = GraphicsEngine::GetInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	swapChain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//FOR SLIDE 13
	vertex list[] =
	{
		//X - Y - Z
		{-0.8f,-0.8f,0.0f,    -0.32f,-0.11f,0.0f,   1,0,0,  0,1,1 }, // POS1
		{-0.9f,0.1f,0.0f,     -0.11f,0.78f,0.0f,    1,0,0,  1,1,0 }, // POS2
		{ 0.0f,-0.4f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS2
		{ 0.0f,0.1f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,1,0 }
	};
	

	m_vertex_buffer = GraphicsEngine::GetInstance()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::GetInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::GetInstance()->createVertexShader(shader_byte_code, size_shader);
	m_vertex_buffer->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::GetInstance()->releaseCompiledShader();


	GraphicsEngine::GetInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::GetInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::GetInstance()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::GetInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 1.0f, 1.0f, 1.0f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	constant cc;



	//FOR SLIDE 13
	//forward time is enabled at start
	if(isForwardTime == true)
	{
		//continue animation until it reaches 8 seconds
		if(animationTicks < 8.0f)
		{
			animationTicks += EngineTime::getDeltaTime();
			m_angle += 1.57f * EngineTime::getDeltaTime() * animationTicks;
			cc.m_angle = m_angle;
		}
		//turn forward time to false as it exceeds 8 seconds to make it backward time
		else
			isForwardTime = false;
	}

	//when backward time is enabled
	if(isForwardTime == false)
	{
		//continue animation as current animation ticks reach down to zero
		if (animationTicks > 0.0f)
		{
			animationTicks -= EngineTime::getDeltaTime();
			m_angle += 1.57f * EngineTime::getDeltaTime() * animationTicks;
			cc.m_angle = m_angle;
		}
		//turn forward time back to true when it goes below zero
		else
			isForwardTime = true;
	}
	//END OF FOR SLIDE 13





	m_cb->update(GraphicsEngine::GetInstance()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::GetInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vertex_buffer->getSizeVertexList(), 0);
	swapChain->present(true);
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