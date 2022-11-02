#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "EngineTime.h"

class Camera : public AGameObject, public InputListener
{
public:
	Camera(std::string name);
	~Camera();

	void update(float deltaTime) override;
	Matrix4x4 getViewMatrix();
	Matrix4x4 getMatrix();
	Matrix4x4 getCamProjMatrix();

	//inherited from input listener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

	void draw(float width, float height) override;

private:
	void updateViewMatrix();

	float mouseDown = false;

	float forward = 0.0f;
	float right = 0.0f;
	float up = 0.0f;
	float camSpeed = 0.5f;

	Matrix4x4 viewCamera;
	float fovInDegrees = 90.0f;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;
};

