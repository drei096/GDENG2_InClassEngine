#include "PlanePrimitive.h"

#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

PlanePrimitive::PlanePrimitive(std::string name, ShaderTypes shaderType) : CubePrimitive(name, shaderType)
{
	AssignVertexAndPixelShaders(shaderType);
	this->cubeShaderType = shaderType;


	setVertexList(shaderType);

	this->vertexBuffer = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexBuffer();

	setIndexList();


	indexBuffer = GraphicsEngine::GetInstance()->getRenderingSystem()->createIndexBuffer();
	indexBuffer->load(index_list, getIndexListSize());
	
	void* shader_byte_code = nullptr;
	size_t size_of_shader = 0;


	//CREATING VERTEX SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compileVertexShader(this->vertexShaderFile, "vsmain", &shader_byte_code, &size_of_shader);
	m_vs = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexShader(shader_byte_code, size_of_shader);
	vertexBuffer->load(getVertexList(), sizeof(flatColorVertex), getVertexListSize(), shader_byte_code, size_of_shader, shaderType);
	GraphicsEngine::GetInstance()->getRenderingSystem()->releaseCompiledShader();

	//CREATING PIXEL SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compilePixelShader(this->pixelShaderFile, "psmain", &shader_byte_code, &size_of_shader);
	m_ps = GraphicsEngine::GetInstance()->getRenderingSystem()->createPixelShader(shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->getRenderingSystem()->releaseCompiledShader();

	//CREATING CONSTANT BUFFER
	m_cb = GraphicsEngine::GetInstance()->getRenderingSystem()->createConstantBuffer();
	cc.m_angle = 0.0f;
	m_cb->load(&cc, sizeof(constantData));

	//set default shaders
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	this->setPosition(0.0f, 0.0f, 0.0f);
	this->setScale(50.0f, 0.01f, 50.0f);
	this->setRotation(0.0f, 0.0f, 0.0f);
}

PlanePrimitive::~PlanePrimitive()
{
}

void PlanePrimitive::update(float deltaTime)
{
	std::cout << this->name << " " << "is updating" << std::endl;
}

void PlanePrimitive::setVertexList(ShaderTypes shaderType)
{
	if (shaderType == ShaderTypes::ALBEDO)
	{
		//FRONT FACE OF CUBE
		vertex_list[0] = { Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,1,1) };
		vertex_list[1] = { Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,1) };
		vertex_list[2] = { Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,1) };
		vertex_list[3] = { Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,1,1) };

		//BACK FACE OF CUBE
		vertex_list[4] = { Vector3D(0.5f,-0.5f,0.5f),    Vector3D(1,1,1) };
		vertex_list[5] = { Vector3D(0.5f,0.5f,0.5f),    Vector3D(1,1,1) };
		vertex_list[6] = { Vector3D(-0.5f,0.5f,0.5f),   Vector3D(1,1,1) };
		vertex_list[7] = { Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(1,1,1) };
	}
	else if (shaderType == ShaderTypes::LERPING_ALBEDO)
	{
		//FRONT FACE OF CUBE
		vertex_list[0] = { Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0), Vector3D(1,0,1) };
		vertex_list[1] = { Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0) , Vector3D(0,0,1) };
		vertex_list[2] = { Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0) , Vector3D(0,1,0) };
		vertex_list[3] = { Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0) , Vector3D(0.25f,0,0.5f) };

		//BACK FACE OF CUBE
		vertex_list[4] = { Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0) , Vector3D(0,0,1) };
		vertex_list[5] = { Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1) , Vector3D(1,0,0) };
		vertex_list[6] = { Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1) , Vector3D(1,0,1) };
		vertex_list[7] = { Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0) , Vector3D(0.7f,0.25f,0.6f) };
	}
}




