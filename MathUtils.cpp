#include "MathUtils.h"
#include <cstdlib>

float MathUtils::randomFloat(float a, float b)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int MathUtils::randomInt(int a, int b)
{
    int range = a - b + 1;
    int num = rand() % range + a;

    return num;
}

float MathUtils::minValue(const float a, const float b)
{
    return (a < b) ? a : b;
}

float MathUtils::maxValue(float a, float b)
{
    return (a < b) ? b : a;
}

float MathUtils::lerp(float startVal, float endVal, float percentage)
{
    return startVal + (endVal - startVal) * percentage;
}
