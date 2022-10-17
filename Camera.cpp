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
	/*
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.x;
	float y = localPos.y;
	float z = localPos.z;
	float moveSpeed = 10.0f;

	std::cout << "(" << x << "," << y << "," << z << ")" << std::endl;

	if(this->mouseDown)
	{
		if (InputSystem::GetInstance()->isKeyDown('W'))
		{
			z += deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
		if (InputSystem::GetInstance()->isKeyDown('E'))
		{
			y += deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
		if (InputSystem::GetInstance()->isKeyDown('S'))
		{
			z -= deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
		if (InputSystem::GetInstance()->isKeyDown('Q'))
		{
			y -= deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
		if (InputSystem::GetInstance()->isKeyDown('A'))
		{
			x -= deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
		if (InputSystem::GetInstance()->isKeyDown('D'))
		{
			x += deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
	}
	*/

	
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->viewCamera;
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

		float speed = 0.005f;
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

	//temp.setTranslationMatrix(this->getLocalPosition());
	//worldCam *= temp;


	worldCam.inverse();
	this->viewCamera = worldCam;
}



