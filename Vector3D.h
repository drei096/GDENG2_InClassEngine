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

	Vector3D operator -(Vector3D vec)
	{
		return Vector3D(x - vec.x, y - vec.y, z - vec.z);
	}

	float getMagnitude(Vector3D vec)
	{
		return sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
	}

	static Vector3D getUnitVector(Vector3D vec)
	{
		float magnitude = vec.getMagnitude(vec);
		return Vector3D( (vec.x * (1 / magnitude)), (vec.y * (1 / magnitude)), (vec.z * (1 / magnitude)));
	}

	static Vector3D cross(Vector3D v1, Vector3D v2)
	{
		return Vector3D((v1.y * v2.z) - (v1.z * v2.y), (v1.x * v2.z) - (v1.z * v2.x), (v1.x * v2.y) - (v1.y * v2.x));
	}

	static Vector3D getSurfaceNormal(Vector3D v1, Vector3D v2, Vector3D v3)
	{
		return getUnitVector(cross(v2 - v1, v3 - v1));
	}

public:
	float x;
	float y;
	float z;
};