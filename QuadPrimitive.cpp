#include "QuadPrimitive.h"

QuadPrimitive::QuadPrimitive()
{
	
}

void QuadPrimitive::setVertexList(float posx, float posy, float posz, float r, float g, float b)
{
	list[0] = { -posx, -posy, posz, r, g, b };
	list[1] = { -posx, posy, posz, r,g,b };
	list[2] = { posx, -posy, posz, r,g,b };
	list[3] = { posx, posy, posz, r,g,b };
}

void* QuadPrimitive::getVertexList()
{
	return list;
}

UINT QuadPrimitive::getVertexListSize()
{
	return ARRAYSIZE(list);
}




