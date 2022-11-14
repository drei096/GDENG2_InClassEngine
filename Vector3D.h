#pragma once

#include <cmath>

class Vector3D
{
public:
	Vector3D() : x(0), y(0), z(0)
	{
	}

	Vector3D(float x, float y, float z) : x(x), y(y), z(z)
	{
	}

	Vector3D(const Vector3D& vector) : x(vector.x), y(vector.y), z(vector.z)
	{
	}

	~Vector3D()
	{
		
	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);
		v.z = start.z * (1.0f - delta) + end.z * (delta);
		return v;
	}

	Vector3D operator *(float num)
	{
		return Vector3D(x * num, y * num, z * num);
	}

	

	Vector3D operator +(Vector3D vec)
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3D operator -(Vector3D vec)
	{
		return Vector3D(x - vec.x, y - vec.y, z - vec.z);
	}

	static Vector3D zeros()
	{
		return Vector3D(0.0f, 0.0f, 0.0f);
	}

	static Vector3D ones()
	{
		return Vector3D(1.0f, 1.0f, 1.0f);
	}

	float getMagnitude(Vector3D vec)
	{
		return sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
	}

	static Vector3D getUnitVector(Vector3D vec)
	{
		float magnitude = vec.getMagnitude(vec);
		return Vector3D((vec.x * (1 / magnitude)), (vec.y * (1 / magnitude)), (vec.z * (1 / magnitude)));
	}

	float dotProd(Vector3D v1, Vector3D v2) //function for multiplying vector values; returns total value of vector products"sum"
	{
		float sum = 0;

		sum = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

		return sum;
	}

public:
	float x;
	float y;
	float z;
};