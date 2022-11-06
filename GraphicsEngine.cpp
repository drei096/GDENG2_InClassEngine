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

	return true;
}

bool GraphicsEngine::release()
{
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



