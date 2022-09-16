#pragma once
#include <memory>
#include "Vector3D.h"

class Matrix4x4
{
public:
	Matrix4x4()
	{
	}

	void setIdentity()
	{
		//fill the [4][4] matrix with zeroes
		::memset(matrix, 0, sizeof(float) * 16);

		//hardset the middle values with 1
		matrix[0][0] = 1;
		matrix[1][1] = 1;
		matrix[2][2] = 1;
		matrix[3][3] = 1;
	}

	void setTranslationMatrix(const Vector3D& translationAmount)
	{
		//fill the [4][4] matrix with zeroes
		setIdentity();

		//hardset the trans values with the passed param
		matrix[3][0] = translationAmount.x;
		matrix[3][1] = translationAmount.y;
		matrix[3][2] = translationAmount.z;
	}

	void setScale(const Vector3D& scale)
	{
		setIdentity();
		matrix[0][0] = scale.x;
		matrix[1][1] = scale.y;
		matrix[2][2] = scale.z;
	}

	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();

		matrix[0][0] = 2.0f / width;
		matrix[1][1] = 2.0f / height;
		matrix[2][2] = 1.0f / (far_plane - near_plane);
		matrix[3][2] = -(near_plane / (far_plane - near_plane));
	}

	void operator *=(const Matrix4x4& passedMatrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.matrix[i][j] =
					this->matrix[i][0] * passedMatrix.matrix[0][j] + this->matrix[i][1] * passedMatrix.matrix[1][j] +
					this->matrix[i][2] * passedMatrix.matrix[2][j] + this->matrix[i][3] * passedMatrix.matrix[3][j];
			}
		}

		::memcpy(this->matrix, out.matrix, sizeof(float) * 16);
	}

	void setQuaternionRotation(float theta, float x, float y, float z)
	{
		float normU, qx, qy, qz, qw;

		//normalizing axis vector
		normU = sqrt((x * x) + (y * y) + (z * z));
		qx = x / normU;
		qy = y / normU;
		qz = z / normU;

		//quaternion q setup
		qw = cos(theta / 2);
		qx = qx * sin(theta / 2);
		qy = qy * sin(theta / 2);
		qz = qz * sin(theta / 2);

		//set the rotation matrix

		this->matrix[0][0] = (qw * qw) + (qx * qx) - (qy * qy) - (qz * qz);
		this->matrix[0][1] = (2 * qx * qy) - (2 * qw * qz);
		this->matrix[0][2] = (2 * qx * qz) + (2 * qw * qy);
		this->matrix[0][3] = 0;

		this->matrix[1][0] = (2 * qx * qy) + (2 * qw * qz);
		this->matrix[1][1] = (qw * qw) - (qx * qx) + (qy * qy) - (qz * qz);
		this->matrix[1][2] = (2 * qy * qz) - (2 * qw * qx);
		this->matrix[1][3] = 0;

		this->matrix[2][0] = (2 * qx * qz) - (2 * qw * qy);
		this->matrix[2][1] = (2 * qy * qz) + (2 * qw * qx);
		this->matrix[2][2] = (qw * qw) - (qx * qx) - (qy * qy) + (qz * qz);
		this->matrix[2][3] = 0;
	}

	void setEulerRotationX(float x)
	{
		this->matrix[1][1] = cos(x);
		this->matrix[1][2] = sin(x);
		this->matrix[2][1] = -sin(x);
		this->matrix[2][2] = cos(x);
	}

	void setEulerRotationY(float y)
	{
		this->matrix[0][0] = cos(y);
		this->matrix[0][2] = -sin(y);
		this->matrix[2][0] = sin(y);
		this->matrix[2][2] = cos(y);
	}

	void setEulerRotationZ(float z)
	{
		this->matrix[0][0] = cos(z);
		this->matrix[0][1] = sin(z);
		this->matrix[1][0] = -sin(z);
		this->matrix[1][1] = cos(z);
	}

	~Matrix4x4()
	{ 

	}

public:
	float matrix[4][4] = {};
};
