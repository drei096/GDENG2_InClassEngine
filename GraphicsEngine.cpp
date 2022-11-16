#include "GraphicsEngine.h"
#include "RenderingSystem.h"



GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	
	m_renderingSystem = new RenderingSystem();
	m_renderingSystem->init();

	m_tex_manager = new TextureManager();
	m_mesh_manager = new MeshManager();

	void* shader_byte_code = nullptr;
	UINT size_of_shader = 0;

	//CREATING VERTEX SHADER FOR MESH
	m_renderingSystem->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_of_shader);
	::memcpy(mesh_layout_byte_code, shader_byte_code, size_of_shader);
	mesh_layout_size = size_of_shader;
	m_renderingSystem->releaseCompiledShader();

	return true;
}

bool GraphicsEngine::release()
{
	delete m_mesh_manager;
	delete m_tex_manager;

	m_renderingSystem->release();
	delete m_renderingSystem;
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

GraphicsEngine* GraphicsEngine::GetInstance()
{
	static GraphicsEngine engine;
	return &engine;
}

RenderingSystem* GraphicsEngine::getRenderingSystem()
{
	return m_renderingSystem;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = mesh_layout_byte_code;
	*size = mesh_layout_size;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return m_mesh_manager;
}



