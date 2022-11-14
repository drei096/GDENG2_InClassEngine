#pragma once

#include "Vector3D.h"

class MathUtils
{
public:
	static float randomFloat(float a, float b);
	static int randomInt(int a, int b);
	static float minValue(float a, float b);
	static float maxValue(float a, float b);
	static float distance3D(Vector3D a, Vector3D b);
};

