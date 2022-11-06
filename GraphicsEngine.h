#pragma once
#include<d3d11.h>
#include "Prerequisites.h"
#include "RenderingSystem.h"
#include "TextureManager.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();
	bool release();
	~GraphicsEngine();
	static GraphicsEngine* GetInstance();
	RenderingSystem* getRenderingSystem();
	TextureManager* getTextureManager();

private:
	RenderingSystem* m_renderingSystem = nullptr;
	TextureManager* m_tex_manager = nullptr;
};

