#pragma once
class MathUtils
{
public:
	static float randomFloat(float a, float b);
	static int randomInt(int a, int b);
	static float minValue(float a, float b);
	static float maxValue(float a, float b);
	static float lerp(float startVal, float endVal, float percentage);
};

