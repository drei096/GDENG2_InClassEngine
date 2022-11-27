#include "AGameObject.h"
#include "ShaderCollection.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Vector3D.h"



AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeros();
	this->localRotation = Vector3D::zeros();
	this->localScale = Vector3D::ones();
}

bool AGameObject::release()
{
	if (!componentList.empty())
		return false;
	ComponentList::iterator a;
	for (a = componentList.begin(); a != componentList.end(); a++)
	{
		(*a)->DetachOwner();
		delete (*a);
	}
	componentList.clear();

	if (m_cb->release() && m_vs->release() && m_ps->release() && indexBuffer->release() && vertexBuffer->release())
		return true;

	return false;
}


void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

Matrix4x4 AGameObject::GetMatrix()
{
	return localMatrix;
}

Vector3D AGameObject::getObjectCenterOffset()
{
	return objectCenterOffset;
}

float AGameObject::getBoundingSphereValue()
{
	return boundingSphereValue;
}

std::string AGameObject::getName()
{
	return this->name;
}

bool AGameObject::isEnabled()
{
	return this->enabled;
}

void AGameObject::AttachComponent(AComponent* component)
{
	componentList.push_back(component);
	component->AttachOwner(this);
}

void AGameObject::DetachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponent* AGameObject::FindComponentByName(String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetName() == name) {
			return this->componentList[i];
		}
	}

	return nullptr;
}

AComponent* AGameObject::FindComponentOfType(AComponent::ComponentType type, String name)
{
	if (name.empty())
	{
		for (int i = 0; i < componentList.size(); i++) {
			if (componentList[i]->GetType() == type) {
				return componentList[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < componentList.size(); i++) {
			if (componentList[i]->GetName() == name && componentList[i]->GetType() == type) {
				return componentList[i];
			}
		}
	}

	return nullptr;
}

AGameObject::ComponentList AGameObject::GetComponentsOfType(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

AGameObject::ComponentList AGameObject::GetComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

float* AGameObject::GetPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix;
	allMatrix.setIdentity();

	Matrix4x4 translationMatrix;
	translationMatrix.setIdentity();
	translationMatrix.setTranslationMatrix(this->getLocalPosition());

	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(Vector3D::ones()); //physics 3D only accepts uniform scale for rigidbody

	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix;
	xMatrix.setIdentity();
	xMatrix.setEulerRotationX(rotation.x);
	
	Matrix4x4 yMatrix;
	yMatrix.setIdentity();
	yMatrix.setEulerRotationY(rotation.y);

	Matrix4x4 zMatrix;
	zMatrix.setIdentity();
	zMatrix.setEulerRotationZ(rotation.z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(rotMatrix.multiplyTo(scaleMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	return allMatrix.GetMatrix();
}

void AGameObject::RecomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix;
	newMatrix.setIdentity();
	newMatrix.setMatrix(matrix4x4);

	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(localScale);

	newMatrix *= scaleMatrix;

	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();

	rotMatrix.setEulerRotationX(localRotation.x);
	newMatrix *= rotMatrix;
	rotMatrix.setIdentity();

	rotMatrix.setEulerRotationY(localRotation.y);
	newMatrix *= rotMatrix;
	rotMatrix.setIdentity();

	rotMatrix.setEulerRotationZ(localRotation.z);
	newMatrix *= rotMatrix;

	Matrix4x4 transMatrix;
	transMatrix.setIdentity();
	transMatrix.setTranslationMatrix(localPosition);
	newMatrix *= transMatrix;
	localMatrix = newMatrix;
	this->overrideMatrix = true;
}


