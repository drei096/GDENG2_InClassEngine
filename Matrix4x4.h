#pragma once
#include <memory>
#include <cmath>
#include "Vector3D.h"
#include "Vector4D.h"
#include "DirectXMath.h"

class Matrix4x4
{
public:
	Matrix4x4()
	{
	}

	float* GetMatrix()
	{
		return *matrix;
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

	void setPerspectiveFOVLH(float fov, float aspect, float znear, float zfar)
	{
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;

		matrix[0][0] = xscale;
		matrix[1][1] = yscale;
		matrix[2][2] = zfar / (zfar - znear);
		matrix[2][3] = 1.0f;
		matrix[3][2] = (-znear * zfar) / (zfar - znear);
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

	Matrix4x4 multiplyTo(const Matrix4x4& matrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				out.matrix[i][j] =
					this->matrix[i][0] * matrix.matrix[0][j] + this->matrix[i][1] * matrix.matrix[1][j] +
					this->matrix[i][2] * matrix.matrix[2][j] + this->matrix[i][3] * matrix.matrix[3][j];
			}
		}

		return out;
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
		setIdentity();
		this->matrix[1][1] = cos(x);
		this->matrix[1][2] = sin(x);
		this->matrix[2][1] = -sin(x);
		this->matrix[2][2] = cos(x);
	}

	void setEulerRotationY(float y)
	{
		setIdentity();
		this->matrix[0][0] = cos(y);
		this->matrix[0][2] = -sin(y);
		this->matrix[2][0] = sin(y);
		this->matrix[2][2] = cos(y);
	}

	void setEulerRotationZ(float z)
	{
		setIdentity();
		this->matrix[0][0] = cos(z);
		this->matrix[0][1] = sin(z);
		this->matrix[1][0] = -sin(z);
		this->matrix[1][1] = cos(z);
	}

	void setMatrix(const Matrix4x4& matrix)
	{
		::memcpy(this->matrix, matrix.matrix, sizeof(float) * 16);
	}

	void setMatrix(float matrix[16])
	{
		Matrix4x4 out;
		int index = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.matrix[i][j] = matrix[index];
			}
		}
		setMatrix(out);
	}

	void setMatrix(float matrix[4][4])
	{	
		::memcpy(this->matrix, matrix, sizeof(float) * 16);
	}

	float getDeterminant()
	{
		Vector4D minor, v1, v2, v3;
		float det;

		v1 = Vector4D(this->matrix[0][0], this->matrix[1][0], this->matrix[2][0], this->matrix[3][0]);
		v2 = Vector4D(this->matrix[0][1], this->matrix[1][1], this->matrix[2][1], this->matrix[3][1]);
		v3 = Vector4D(this->matrix[0][2], this->matrix[1][2], this->matrix[2][2], this->matrix[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->matrix[0][3] * minor.x + this->matrix[1][3] * minor.y + this->matrix[2][3] * minor.z +
			this->matrix[3][3] * minor.w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (this->matrix[j][0]);
					vec[a].y = (this->matrix[j][1]);
					vec[a].z = (this->matrix[j][2]);
					vec[a].w = (this->matrix[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.matrix[0][i] = pow(-1.0f, i) * v.x / det;
			out.matrix[1][i] = pow(-1.0f, i) * v.y / det;
			out.matrix[2][i] = pow(-1.0f, i) * v.z / det;
			out.matrix[3][i] = pow(-1.0f, i) * v.w / det;
		}

		this->setMatrix(out);
	}

	Vector3D getZDirection()
	{
		return Vector3D(matrix[2][0], matrix[2][1], matrix[2][2]);
	}

	Vector3D getXDirection()
	{
		return Vector3D(matrix[0][0], matrix[0][1], matrix[0][2]);
	}

	Vector3D getYDirection()
	{
		return Vector3D(matrix[1][0], matrix[1][1], matrix[1][2]);
	}

	Vector3D getTranslation()
	{
		return Vector3D(matrix[3][0], matrix[3][1], matrix[3][2]);
	}

	//FOR OBJECT PICKING, CODE SUBJECT TO REVIEW
	static Vector3D Vector3Transform(const Vector3D& inVector, Matrix4x4 inMatrix)
	{
		Matrix4x4 temp;
		temp.setIdentity();
		temp.matrix[3][0] = inVector.x;
		temp.matrix[3][1] = inVector.y;
		temp.matrix[3][2] = inVector.z;
		temp.matrix[3][3] = 1.0f;

		temp = temp.multiplyTo(inMatrix);
		return Vector3D(temp.matrix[3][0], temp.matrix[3][1], temp.matrix[3][2]);
	}

	//FOR OBJECT PICKING, CODE SUBJECT TO REVIEW
	static Vector3D Vector3TransformNormal(const Vector3D& inVector, Matrix4x4 inMatrix)
	{
		Matrix4x4 temp;
		temp.setIdentity();
		temp.matrix[3][0] = inVector.x;
		temp.matrix[3][1] = inVector.y;
		temp.matrix[3][2] = inVector.z;
		temp.matrix[3][3] = 0.0f;

		temp = temp.multiplyTo(inMatrix);
		return Vector3D(temp.matrix[3][0], temp.matrix[3][1], temp.matrix[3][2]);
	}

	Vector4D multiplyTo(Vector4D inVector)
	{

		Vector4D outVector;

		outVector.x = (inVector.x * this->matrix[0][0]) + (inVector.y * this->matrix[1][0]) + (inVector.z * this->matrix[2][0]) + (inVector.w * this->matrix[3][0]);
		outVector.y = (inVector.x * this->matrix[0][1]) + (inVector.y * this->matrix[1][1]) + (inVector.z * this->matrix[2][1]) + (inVector.w * this->matrix[3][1]);
		outVector.z = (inVector.x * this->matrix[0][2]) + (inVector.y * this->matrix[1][2]) + (inVector.z * this->matrix[2][2]) + (inVector.w * this->matrix[3][2]);
		outVector.w = (inVector.x * this->matrix[0][3]) + (inVector.y * this->matrix[1][3]) + (inVector.z * this->matrix[2][3]) + (inVector.w * this->matrix[3][3]);

		/*
		outVector.x = inVector.x * (this->matrix[0][0] + this->matrix[0][1] + this->matrix[0][2] + this->matrix[0][3]);
		outVector.y = inVector.y * (this->matrix[1][0] + this->matrix[1][1] + this->matrix[1][2] + this->matrix[1][3]);
		outVector.z = inVector.z * (this->matrix[2][0] + this->matrix[2][1] + this->matrix[2][2] + this->matrix[2][3]);
		outVector.w = inVector.w * (this->matrix[3][0] + this->matrix[3][1] + this->matrix[3][2] + this->matrix[3][3]);
		*/
		/*out.x = in.getX() * (this->matrix[0][0] + this->matrix[1][0] + this->matrix[2][0] + this->matrix[3][0]);
		out.y = in.getY() * (this->matrix[0][1] + this->matrix[1][1] + this->matrix[2][1] + this->matrix[3][1]);
		out.z = in.getZ() * (this->matrix[0][2] + this->matrix[1][2] + this->matrix[2][2] + this->matrix[3][2]);
		out.w = in.getW() * (this->matrix[0][3] + this->matrix[1][3] + this->matrix[2][3] + this->matrix[3][3]);*/

		return outVector;
	}

	~Matrix4x4()
	{ 

	}

public:
	float matrix[4][4] = {};
};
