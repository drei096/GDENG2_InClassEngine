#include "PlanePrimitive.h"
#include "GraphicsEngine.h"
#include "ViewportCameraManager.h"

PlanePrimitive::PlanePrimitive(std::string name) : CubePrimitive(name)
{
	setVertexList();
	

	this->vertexBuffer = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexBuffer();

	setIndexList();


	indexBuffer = GraphicsEngine::GetInstance()->getRenderingSystem()->createIndexBuffer();
	indexBuffer->load(index_list, getIndexListSize());
	
	void* shader_byte_code = nullptr;
	UINT size_of_shader = 0;


	//CREATING VERTEX SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_of_shader);
	m_vs = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexShader(shader_byte_code, size_of_shader);
	vertexBuffer->load(getVertexList(), sizeof(vertex), getVertexListSize(), shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->getRenderingSystem()->releaseCompiledShader();

	//CREATING PIXEL SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_of_shader);
	m_ps = GraphicsEngine::GetInstance()->getRenderingSystem()->createPixelShader(shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->getRenderingSystem()->releaseCompiledShader();

	//CREATING CONSTANT BUFFER
	m_cb = GraphicsEngine::GetInstance()->getRenderingSystem()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constantData));

	//set default shaders
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	this->setScale(10.0f, 0.01f, 10.0f);
	this->setRotation(0.0f, 0.0f, 0.0f);
}

PlanePrimitive::~PlanePrimitive()
{
}

void PlanePrimitive::update(float deltaTime)
{
	
}

void PlanePrimitive::draw(int width, int height)
{
	Matrix4x4 allMatrix;
	allMatrix.setIdentity();

	Matrix4x4 translationMatrix;
	translationMatrix.setIdentity();
	translationMatrix.setTranslationMatrix(this->getLocalPosition());

	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(this->getLocalScale());


	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMatrix;
	zMatrix.setIdentity();
	zMatrix.setQuaternionRotation(rotation.z, 0, 0, 1);

	Matrix4x4 xMatrix;
	xMatrix.setIdentity();
	xMatrix.setQuaternionRotation(rotation.x, 1, 0, 0);

	Matrix4x4 yMatrix;
	yMatrix.setIdentity();
	yMatrix.setQuaternionRotation(rotation.y, 0, 1, 0);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();
	rotMatrix *= zMatrix;
	rotMatrix *= yMatrix;
	rotMatrix *= xMatrix;
	allMatrix *= rotMatrix;


	allMatrix *= scaleMatrix;
	allMatrix *= translationMatrix;
	cc.m_world = allMatrix;

	Matrix4x4 cameraMatrix = ViewportCameraManager::getInstance()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;


	float aspectRatio = (float)width / (float)height;
	cc.m_proj.setPerspectiveFOVLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	this->m_cb->update(GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//set the indices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setIndexBuffer(getIndexBuffer());
	//set the vertices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setVertexBuffer(getVertexBuffer());

	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(getIndexListSize(), 0, 0);
}