#pragma once

#include "CubePrimitive.h"
#include "DeviceContext.h"

class PrimitiveManager
{
public:
	static PrimitiveManager* GetInstance();

	void init();

	//FOR QUADS
	void initQuad(float posx, float posy, float posz, float r, float g, float b, float offsetX, float offsetY, void* shader_byte_code, size_t byte_code_size);
	void DrawQuad();

	//FOR CUBES
	void InitCube();
	void DrawCube(ConstantBuffer* m_cb);

	void release();
};
