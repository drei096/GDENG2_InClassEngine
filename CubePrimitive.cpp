#include "CubePrimitive.h"
#include "GraphicsEngine.h"
#include "ViewportCameraManager.h"


CubePrimitive::CubePrimitive(std::string name) : AGameObject(name)
{

	setVertexList();

	vertexBuffer = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexBuffer();

	setIndexList();

	indexBuffer = GraphicsEngine::GetInstance()->getRenderingSystem()->createIndexBuffer();
	indexBuffer->load(index_list, getIndexListSize());

	void* shader_byte_code = nullptr;
	UINT size_of_shader = 0;

	//CREATING VERTEX SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_of_shader);
	m_vs = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexShader(shader_byte_code, size_of_shader);
	vertexBuffer->load(vertex_list, sizeof(vertex), getVertexListSize(), shader_byte_code, size_of_shader);
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

	

	
	
}

void* CubePrimitive::getVertexList()
{
	return vertex_list;
}

UINT CubePrimitive::getVertexListSize()
{
	return ARRAYSIZE(vertex_list);
}

void CubePrimitive::setVertexList()
{
	//FRONT FACE OF CUBE
	vertex_list[0] = { Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0) };
	vertex_list[1] = { Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0) };
	vertex_list[2] = { Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0) };
	vertex_list[3] = { Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0) };

	//BACK FACE OF CUBE
	vertex_list[4] = { Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0) };
	vertex_list[5] = { Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1) };
	vertex_list[6] = { Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1) };
	vertex_list[7] = { Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0) };
}

void CubePrimitive::setIndexList()
{
	//CREATING INDEX BUFFER
	unsigned int cube_index_list[] =
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

	for(int i = 0; i < 36; i++)
	{
		index_list[i] = cube_index_list[i];
	}
}

void* CubePrimitive::getIndexList()
{
	return index_list;
}

UINT CubePrimitive::getIndexListSize()
{
	return ARRAYSIZE(index_list);
}

VertexBuffer* CubePrimitive::getVertexBuffer()
{
	return this->vertexBuffer;
}

IndexBuffer* CubePrimitive::getIndexBuffer()
{
	return this->indexBuffer;
}

ConstantBuffer* CubePrimitive::getConstantBuffer()
{
	return this->m_cb;
}

void* CubePrimitive::getCBData()
{
	return &cc;
}

void CubePrimitive::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	if (InputSystem::GetInstance()->isKeyDown('W'))
	{
		this->ticks += deltaTime;

		float rotSpeed = this->ticks * this->speed * this->animSpeed;
		this->setRotation(rotSpeed, rotSpeed, rotSpeed);
	}
	else if (InputSystem::GetInstance()->isKeyDown('S'))
	{
		this->ticks -= deltaTime;

		float rotSpeed = this->ticks * this->speed * this->animSpeed;
		this->setRotation(rotSpeed, rotSpeed, rotSpeed);
	}
}

void CubePrimitive::draw(float width, float height)
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
	xMatrix.setQuaternionRotation(rotation.x, 1,0,0);

	Matrix4x4 yMatrix;
	yMatrix.setIdentity();
	yMatrix.setQuaternionRotation(rotation.y, 0,1,0);

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
	//cc.m_proj.setPerspectiveFOVLH(1.57f, aspectRatio, 0.1f, 100.0f);
	cc.m_proj.setOrthoLH
	(
		width / 400.0f,
		height / 400.0f,
		-4.0f,
		4.0f
	);

	this->m_cb->update(GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//set the indices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setIndexBuffer(getIndexBuffer());
	//set the vertices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setVertexBuffer(getVertexBuffer());

	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(getIndexListSize(), 0, 0);
}

void CubePrimitive::setAnimSpeed(float value)
{
	this->animSpeed = value;
}

bool CubePrimitive::release()
{
	if (vertexBuffer->release() && indexBuffer->release())
		return true;
	else
		return false;
}


