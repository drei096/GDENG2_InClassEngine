#pragma once
#include "AGameObject.h"
#include "InputListener.h"

class Camera : public AGameObject, public InputListener
{
public:
	Camera(std::string name);
	~Camera();

	void update(float deltaTime) override;
	Matrix4x4 getViewMatrix();

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

	float ticks = 0.0f;
	float mouseDown = false;
};

