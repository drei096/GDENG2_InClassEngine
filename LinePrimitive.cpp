#include "LinePrimitive.h"

LinePrimitive::LinePrimitive(std::string name, Vector3D origin, Vector3D line) : AGameObject(name)
{
	vertex vertex_list[] =
	{
		{origin, Vector3D(1,0,0)},
		{line, Vector3D(1,0,0)}
	};

	vertexBuffer = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexBuffer();


	void* shader_byte_code = nullptr;
	UINT size_of_shader = 0;

	//CREATING VERTEX SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_of_shader);
	m_vs = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexShader(shader_byte_code, size_of_shader);
	vertexBuffer->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shader_byte_code, size_of_shader, ShaderTypes::ALBEDO);
	GraphicsEngine::GetInstance()->getRenderingSystem()->releaseCompiledShader();

	//CREATING PIXEL SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_of_shader);
	m_ps = GraphicsEngine::GetInstance()->getRenderingSystem()->createPixelShader(shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->getRenderingSystem()->releaseCompiledShader();
}

void* LinePrimitive::getVertexList()
{
	return nullptr;
}

UINT LinePrimitive::getVertexListSize()
{
	return 0;
}

void LinePrimitive::setVertexList()
{
}

void LinePrimitive::update(float deltaTime)
{
}

void LinePrimitive::draw(float width, float height)
{
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setConstantBuffer(this->m_vs, m_cb);
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setConstantBuffer(this->m_ps, m_cb);

	//set default shaders
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setVertexShader(this->m_vs);
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setPixelShader(this->m_ps);

	//set the vertices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setVertexBuffer(this->getVertexBuffer());


	//draw the line
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->drawLineList(2, 0);
}


VertexBuffer* LinePrimitive::getVertexBuffer()
{
	return this->vertexBuffer;
}
