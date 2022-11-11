#include "LinePrimitive.h"

#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "ViewportCameraManager.h"

LinePrimitive::LinePrimitive(std::string name, Vector3D origin, Vector3D line) : AGameObject(name)
{
	flatColorVertex vertex_list[] =
	{
		{origin, Vector3D(1,0,0)},
		{line, Vector3D(1,0,0)}
	};

	this->vertexBuffer = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexBuffer();


	void* shader_byte_code = nullptr;
	UINT size_of_shader = 0;

	//CREATING VERTEX SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compileVertexShader(L"AlbedoVertexShader.hlsl", "vsmain", &shader_byte_code, &size_of_shader);
	m_vs = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexShader(shader_byte_code, size_of_shader);
	vertexBuffer->load(vertex_list, sizeof(flatColorVertex), ARRAYSIZE(vertex_list), shader_byte_code, size_of_shader, ShaderTypes::ALBEDO);
	GraphicsEngine::GetInstance()->getRenderingSystem()->releaseCompiledShader();

	//CREATING PIXEL SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compilePixelShader(L"AlbedoPixelShader.hlsl", "psmain", &shader_byte_code, &size_of_shader);
	m_ps = GraphicsEngine::GetInstance()->getRenderingSystem()->createPixelShader(shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->getRenderingSystem()->releaseCompiledShader();

	//CREATING CONSTANT BUFFER
	m_cb = GraphicsEngine::GetInstance()->getRenderingSystem()->createConstantBuffer();
	cc.m_angle = 0.0f;
	m_cb->load(&cc, sizeof(constantData));
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
	cc.m_proj = ViewportCameraManager::getInstance()->GetSceneCameraProjectionMatrix();

	this->m_cb->update(GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext(), &cc);
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
