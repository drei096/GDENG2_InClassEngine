#pragma once
#include<d3d11.h>
#include "Prerequisites.h"
#include "RenderingSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"

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
	void getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);
	MeshManager* getMeshManager();

private:
	RenderingSystem* m_renderingSystem = nullptr;
	TextureManager* m_tex_manager = nullptr;
	MeshManager* m_mesh_manager = nullptr;

	unsigned char mesh_layout_byte_code[1024];
	size_t mesh_layout_size = 0;
};

