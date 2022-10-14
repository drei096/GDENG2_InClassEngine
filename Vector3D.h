#pragma once

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

	static Vector3D zeros()
	{
		return Vector3D(0.0f, 0.0f, 0.0f);
	}

	static Vector3D ones()
	{
		return Vector3D(1.0f, 1.0f, 1.0f);
	}

public:
	float x;
	float y;
	float z;
};