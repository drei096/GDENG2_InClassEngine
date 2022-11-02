#pragma once
#include <vector>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Vector3D.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "DeviceContext.h"
#include "AppWindow.h"

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constantData
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};

class AGameObject
{
public:
	AGameObject(std::string name);
	virtual bool release();

	void* getVertexList();
	void setVertexList();
	UINT getVertexListSize();

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	virtual void update(float deltaTime) = 0;
	virtual void draw(float width, float height) = 0;

	std::string getName();
	bool isEnabled();

private:
	friend class PrimitiveManager;

protected:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	ConstantBuffer* m_cb = nullptr;

	constantData cc;

	PixelShader* m_ps;
	VertexShader* m_vs;


	std::string name;
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;
	Matrix4x4 localMatrix;

private:
	bool enabled = true;
};

