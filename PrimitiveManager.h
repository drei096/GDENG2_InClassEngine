#pragma once

#include "QuadPrimitive.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"

class PrimitiveManager
{
public:
	static PrimitiveManager* GetInstance();

	//FOR QUADS
	void initQuad(float posx, float posy, float posz, float r, float g, float b, void* shader_byte_code, size_t byte_code_size);
	void DrawQuad();

	std::vector<QuadPrimitive*> quads;

	void init();
	void release();
};

