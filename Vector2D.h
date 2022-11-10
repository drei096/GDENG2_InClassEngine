#pragma once
#include <cmath>

class Vector2D
{
public:
	Vector2D() : x(0), y(0)
	{
	}

	Vector2D(float x, float y) : x(x), y(y)
	{
	}

	Vector2D(const Vector2D& vector) : x(vector.x), y(vector.y)
	{
	}

	~Vector2D()
	{

	}


	Vector2D operator *(float num)
	{
		return Vector2D(x * num, y * num);
	}



	Vector2D operator +(Vector2D vec)
	{
		return Vector2D(x + vec.x, y + vec.y);
	}

	Vector2D operator -(Vector2D vec)
	{
		return Vector2D(x - vec.x, y - vec.y);
	}

	static Vector2D zeros()
	{
		return Vector2D(0.0f, 0.0f);
	}

	static Vector2D ones()
	{
		return Vector2D(1.0f, 1.0f);
	}

	
	

public:
	float x;
	float y;
};

