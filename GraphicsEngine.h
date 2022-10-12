#pragma once
#include<d3d11.h>
#include "Prerequisites.h"
#include "RenderingSystem.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();
	bool release();
	~GraphicsEngine();
	static GraphicsEngine* GetInstance();
	RenderingSystem* getRenderingSystem();

private:
	RenderingSystem* m_renderingSystem = nullptr;
};

