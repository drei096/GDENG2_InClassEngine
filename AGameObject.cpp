#include "AGameObject.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeros();
	this->localRotation = Vector3D::zeros();
}


void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

std::string AGameObject::getName()
{
	return this->name;
}

bool AGameObject::isEnabled()
{
	return this->enabled;
}


