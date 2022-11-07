#include "Camera.h"

#include <iostream>

Camera::Camera(std::string name) : AGameObject(name)
{
	this->setPosition(0.0f, 0.0f, -2.0f);
	
	this->updateViewMatrix();
	InputSystem::GetInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::GetInstance()->removeListener(this);
}

void Camera::update(float deltaTime)
{

	
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->viewCamera;
}

Matrix4x4 Camera::getMatrix()
{
	return this->localMatrix;
}

Matrix4x4 Camera::getCamProjMatrix()
{
	int width = Window::WIDTH;
	int height = Window::HEIGHT;
	float aspectRatio = (float)width / (float)height;
	float fov = fovInDegrees * (3.1415926f / 180.0f);

	Matrix4x4 projectionMatrix;
	projectionMatrix.setPerspectiveFOVLH(fov, aspectRatio, nearPlane, farPlane);

	return projectionMatrix;
}

void Camera::onKeyDown(int key)
{
	if (this->mouseDown)
	{
		if (InputSystem::GetInstance()->isKeyDown('W'))
		{
			forward = 1.0f;
		}
		if (InputSystem::GetInstance()->isKeyDown('E'))
		{
			up = 1.0f;
		}
		if (InputSystem::GetInstance()->isKeyDown('S'))
		{
			forward = -1.0f;
		}
		if (InputSystem::GetInstance()->isKeyDown('Q'))
		{
			up = -1.0f;
		}
		if (InputSystem::GetInstance()->isKeyDown('A'))
		{
			right = -1.0f;
		}
		if (InputSystem::GetInstance()->isKeyDown('D'))
		{
			right = 1.0f;
		}

		updateViewMatrix();
	}
}

void Camera::onKeyUp(int key)
{
	forward = 0.0f;
	right = 0.0f;
	up = 0.0f;
}

void Camera::onMouseMove(const Point& mouse_pos)
{
	if (this->mouseDown) 
	{
		Vector3D localRot = this->getLocalRotation();
		float x = localRot.x;
		float y = localRot.y;
		float z = localRot.z;

		float speed = 0.003f;
		x -= mouse_pos.m_y * speed;
		y -= mouse_pos.m_x * speed;

		this->setRotation(x, y, z);
		this->updateViewMatrix();
		
	}
}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{
}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
	this->mouseDown = false;
}

void Camera::draw(float width, float height)
{
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();
	Matrix4x4 temp;
	temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setQuaternionRotation(localRot.x, 1, 0, 0);
	worldCam *= temp;

	temp.setIdentity();
	temp.setQuaternionRotation(localRot.y, 0, 1, 0);
	worldCam *= temp;


	//NEW POSITION FOR FREECAM MOVEMENT
	temp.setIdentity();
	Vector3D new_pos = localMatrix.getTranslation() + worldCam.getZDirection() * (forward * camSpeed);
	new_pos = new_pos + worldCam.getXDirection() * (right * camSpeed);
	new_pos = new_pos + worldCam.getYDirection() * (up * camSpeed);
	temp.setTranslationMatrix(new_pos);
	worldCam *= temp;
	localMatrix = worldCam;



	worldCam.inverse();
	this->viewCamera = worldCam;
}



