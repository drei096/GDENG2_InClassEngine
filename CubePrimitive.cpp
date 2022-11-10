#include "CubePrimitive.h"
#include "GraphicsEngine.h"
#include "ViewportCameraManager.h"
#include <cmath>

CubePrimitive::CubePrimitive(std::string name, ShaderTypes shaderType) : AGameObject(name)
{
	AssignVertexAndPixelShaders(shaderType);
	this->cubeShaderType = shaderType;

	setVertexList(shaderType);

	std::cout << shaderType << std::endl;

	vertexBuffer = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexBuffer();

	setIndexList();

	indexBuffer = GraphicsEngine::GetInstance()->getRenderingSystem()->createIndexBuffer();
	indexBuffer->load(index_list, getIndexListSize());

	void* shader_byte_code = nullptr;
	UINT size_of_shader = 0;

	//CREATING VERTEX SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compileVertexShader(this->vertexShaderFile, "vsmain", &shader_byte_code, &size_of_shader);
	m_vs = GraphicsEngine::GetInstance()->getRenderingSystem()->createVertexShader(shader_byte_code, size_of_shader);

	//set to texturedvertex for now
	vertexBuffer->load(texd_vertex_list, sizeof(texturedVertex), getVertexListSize(), shader_byte_code, size_of_shader, shaderType);

	GraphicsEngine::GetInstance()->getRenderingSystem()->releaseCompiledShader();

	//CREATING PIXEL SHADER
	GraphicsEngine::GetInstance()->getRenderingSystem()->compilePixelShader(this->pixelShaderFile, "psmain", &shader_byte_code, &size_of_shader);
	m_ps = GraphicsEngine::GetInstance()->getRenderingSystem()->createPixelShader(shader_byte_code, size_of_shader);
	GraphicsEngine::GetInstance()->getRenderingSystem()->releaseCompiledShader();

	//CREATING CONSTANT BUFFER
	m_cb = GraphicsEngine::GetInstance()->getRenderingSystem()->createConstantBuffer();
	cc.m_angle = 0.0f;
	m_cb->load(&cc, sizeof(constantData));

	
	this->setPosition(0.0f, 0.0f, 0.0f);
	this->setScale(1.0f, 1.0f, 1.0f);
	this->setRotation(0.0f, 0.0f, 0.0f);
	
	
}

void* CubePrimitive::getVertexList()
{
	return vertex_list;
}

UINT CubePrimitive::getVertexListSize()
{
	return ARRAYSIZE(vertex_list);
}

void CubePrimitive::setVertexList(ShaderTypes shaderType)
{
	if(shaderType == ShaderTypes::ALBEDO)
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
	else if (shaderType == ShaderTypes::FLAT_TEXTURED)
	{
		Vector3D positionList[] =
		{
			{Vector3D(-0.5f,-0.5f,-0.5f)},
			{ Vector3D(-0.5f,0.5f,-0.5f)},
			{ Vector3D(0.5f,0.5f,-0.5f)},
			{ Vector3D(0.5f,-0.5f,-0.5f)},

			//BACK FACE OF CUBE
			{ Vector3D(0.5f,-0.5f,0.5f)},
			{ Vector3D(0.5f,0.5f,0.5f)},
			{ Vector3D(-0.5f,0.5f,0.5f)},
			{ Vector3D(-0.5f,-0.5f,0.5f)}
		};

		Vector2D texcoordList[] =
		{
			{Vector2D(0.0f, 0.0f)},
			{ Vector2D(0.0f, 1.0f)},
			{ Vector2D(1.0f, 0.0f)},
			{ Vector2D(1.0f, 1.0f)},
		};

		//FRONT FACE OF CUBE
		texd_vertex_list[0] = { positionList[0], texcoordList[1]};
		texd_vertex_list[1] = { positionList[1], texcoordList[0] };
		texd_vertex_list[2] = { positionList[2], texcoordList[2] };
		texd_vertex_list[3] = { positionList[3], texcoordList[3] };

		//BACK FACE OF CUBE
		texd_vertex_list[4] = { positionList[4], texcoordList[1] };
		texd_vertex_list[5] = { positionList[5], texcoordList[0] };
		texd_vertex_list[6] = { positionList[6], texcoordList[2] };
		texd_vertex_list[7] = { positionList[7], texcoordList[3] };

		texd_vertex_list[8] = { positionList[1], texcoordList[1] };
		texd_vertex_list[9] = { positionList[6], texcoordList[0] };
		texd_vertex_list[10] = { positionList[5], texcoordList[2] };
		texd_vertex_list[11] = { positionList[2], texcoordList[3] };

		texd_vertex_list[12] = { positionList[7], texcoordList[1] };
		texd_vertex_list[13] = { positionList[0], texcoordList[0] };
		texd_vertex_list[14] = { positionList[3], texcoordList[2] };
		texd_vertex_list[15] = { positionList[4], texcoordList[3] };

		texd_vertex_list[16] = { positionList[3], texcoordList[1] };
		texd_vertex_list[17] = { positionList[2], texcoordList[0] };
		texd_vertex_list[18] = { positionList[5], texcoordList[2] };
		texd_vertex_list[19] = { positionList[4], texcoordList[3] };

		texd_vertex_list[20] = { positionList[7], texcoordList[1] };
		texd_vertex_list[21] = { positionList[6], texcoordList[0] };
		texd_vertex_list[22] = { positionList[1], texcoordList[2] };
		texd_vertex_list[23] = { positionList[0], texcoordList[3] };
	}
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

void CubePrimitive::AssignVertexAndPixelShaders(ShaderTypes shaderType)
{
	ShaderCollection::GetInstance()->getShadersByType(shaderType, &vertexShaderFile, &pixelShaderFile);
}

void CubePrimitive::update(float deltaTime)
{
	
	m_cb->update(GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext(), &cc);
	
	this->animationTicks += deltaTime;

	/*
	scaleSpeed += 0.0001f * deltaTime;

	
	if(this->getLocalScale().x <= 10.0f && this->getLocalScale().y >= 0.01f && this->getLocalScale().z <= 10.0f)
	{
		float xscale = MathUtils::lerp(this->getLocalScale().x, 10.0f, (sin(scaleSpeed)) * animationTicks);
		float yscale = MathUtils::lerp(this->getLocalScale().y, 0.01f, (sin(scaleSpeed)) * animationTicks);
		float zscale = MathUtils::lerp(this->getLocalScale().z, 10.0f, (sin(scaleSpeed)) * animationTicks);

		this->setScale(xscale, yscale, zscale);
	}
	*/
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
	allMatrix *= scaleMatrix;

	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();
	rotMatrix *= zMatrix;
	rotMatrix *= yMatrix;
	rotMatrix *= xMatrix;
	allMatrix *= rotMatrix;

	allMatrix *= translationMatrix;
	cc.m_world = allMatrix;

	Matrix4x4 cameraMatrix = ViewportCameraManager::getInstance()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;

	
	float aspectRatio = (float)width / (float)height;
	cc.m_proj = ViewportCameraManager::getInstance()->GetSceneCameraProjectionMatrix();

	computeBoundingSphere();

	if(cubeShaderType == ShaderTypes::LERPING_ALBEDO)
	{
		cc.m_angle += 1.57f * EngineTime::getDeltaTime();
	}
	
	this->m_cb->update(GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//set default shaders
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//set the indices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setIndexBuffer(getIndexBuffer());
	//set the vertices of the object/cube/triangle to draw
	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->setVertexBuffer(getVertexBuffer());

	GraphicsEngine::GetInstance()->getRenderingSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(getIndexListSize(), 0, 0);
}


void CubePrimitive::computeBoundingSphere()
{
	Vector3D minVertex, maxVertex;
	

	for(int i = 0; i < getVertexListSize(); i++)
	{
		Vector4D vertex4D = Vector4D(vertex_list[i].position, 1.0f);
		Vector4D vertex4DTransformed = Vector4D(cc.m_world.multiplyTo(vertex4D));
		vertex4DTransformed = cc.m_view.multiplyTo(vertex4DTransformed);
		vertex4DTransformed = cc.m_proj.multiplyTo(vertex4DTransformed);
		Vector3D vertex3DTransformed = Vector3D(vertex4DTransformed.x, vertex4DTransformed.y, vertex4DTransformed.z);


		minVertex.x = MathUtils::minValue(minVertex.x, vertex3DTransformed.x);
		minVertex.y = MathUtils::minValue(minVertex.y, vertex3DTransformed.y);    // Find smallest y value in model
		minVertex.z = MathUtils::minValue(minVertex.z, vertex3DTransformed.z);    // Find smallest z value in model

		//Get the largest vertex 
		maxVertex.x = MathUtils::maxValue(maxVertex.x, vertex3DTransformed.x);    // Find largest x value in model
		maxVertex.y = MathUtils::maxValue(maxVertex.y, vertex3DTransformed.y);    // Find largest y value in model
		maxVertex.z = MathUtils::maxValue(maxVertex.z, vertex3DTransformed.z);    // Find largest z value in model
	}


	// Compute distance between maxVertex and minVertex
	float distX = (maxVertex.x - minVertex.x) / 2.0f;
	float distY = (maxVertex.y - minVertex.y) / 2.0f;
	float distZ = (maxVertex.z - minVertex.z) / 2.0f;

	// Now store the distance between (0, 0, 0) in model space to the models real center
	objectCenterOffset = Vector3D(maxVertex.x - distX, maxVertex.y - distY, maxVertex.z - distZ);

	// Compute bounding sphere (distance between min and max bounding box vertices)
	// boundingSphere = sqrt(distX*distX + distY*distY + distZ*distZ) / 2.0f;
	Vector3D distVec = Vector3D(distX, distY, distZ);
	Vector3D temp;
	boundingSphereValue = temp.getMagnitude(distVec);

	//std::cout << boundingSphereValue << std::endl;
}

bool CubePrimitive::release()
{
	return true;
}


