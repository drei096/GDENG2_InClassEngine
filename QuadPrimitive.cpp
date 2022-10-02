#include "QuadPrimitive.h"

QuadPrimitive::QuadPrimitive()
{
	
}

void QuadPrimitive::setVertexList(float posx, float posy, float posz, float r, float g, float b, float offsetX, float offsetY)
{
	list[0] = { -posx + offsetX, -posy + offsetY, posz, r, g, b };
	list[1] = { -posx + offsetX, posy + offsetY, posz, r,g,b };
	list[2] = { posx + offsetX, -posy + offsetY, posz, r,g,b };
	list[3] = { posx + offsetX, posy + offsetY, posz, r,g,b };
}

void* QuadPrimitive::getVertexList()
{
	return list;
}

UINT QuadPrimitive::getVertexListSize()
{
	return ARRAYSIZE(list);
}

bool QuadPrimitive::release()
{
	vertexBuffer->release();

	return true;
}




