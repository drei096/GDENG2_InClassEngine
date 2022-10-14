#include "PrimitiveManager.h"

#include "EngineTime.h"


PrimitiveManager* PrimitiveManager::GetInstance()
{
	static PrimitiveManager primitiveManager;
	return &primitiveManager;
}


void PrimitiveManager::destroy()
{
	GetInstance()->gameObjectMap.clear();
	GetInstance()->gameObjectList.clear();
	
}

AGameObject* PrimitiveManager::findObjectByName(std::string name)
{
	if (this->gameObjectMap[name] != NULL) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

PrimitiveManager::List PrimitiveManager::getAllObjects()
{
	return this->gameObjectList;
}

int PrimitiveManager::activeObjects()
{
	return gameObjectList.size();
}

void PrimitiveManager::updateAll()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		//replace with component update
		if (this->gameObjectList[i]->isEnabled()) {
			this->gameObjectList[i]->update(EngineTime::getDeltaTime());
		}
	}
}

void PrimitiveManager::renderAll(int viewportWidth, int viewportHeight)
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		//replace with component update
		if (this->gameObjectList[i]->isEnabled()) {
			this->gameObjectList[i]->draw(viewportWidth, viewportHeight);
		}
	}
}

void PrimitiveManager::addObject(AGameObject* gameObject)
{
	if (this->gameObjectMap[gameObject->getName()] != NULL) {
		int count = 1;
		String revisedString = gameObject->getName() + " " + "(" + std::to_string(count) + ")";
		while (this->gameObjectMap[revisedString] != NULL) {
			count++;
			revisedString = gameObject->getName() + " " + "(" + std::to_string(count) + ")";
		}
		//std::cout << "Duplicate found. New name is: " << revisedString << "\n";
		gameObject->name = revisedString;
		this->gameObjectMap[revisedString] = gameObject;
	}
	else {
		this->gameObjectMap[gameObject->getName()] = gameObject;
	}

	this->gameObjectList.push_back(gameObject);
}

void PrimitiveManager::createObject(PrimitiveType type)
{
	if (type == PrimitiveType::CUBE) {
		CubePrimitive* cube = new CubePrimitive("Cube");
		cube->setPosition(0.0f, 0.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		cube->setRotation(0.0f, 0.0f, 0.0f);
		this->addObject(cube);
	}

	/*
	if (type == PrimitiveType::PLANE) {
		Plane* plane = new Plane("Plane", shaderByteCode, sizeShader);
		this->addObject(plane);
	}
	*/
}

void PrimitiveManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}

	delete gameObject;
}

void PrimitiveManager::deleteObjectByName(std::string name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != NULL) {
		this->deleteObject(object);
	}
}

void PrimitiveManager::setSelectedObject(std::string name)
{
	if (this->gameObjectMap[name] != NULL) {
		this->setSelectedObject(this->gameObjectMap[name]);
	}
}

void PrimitiveManager::setSelectedObject(AGameObject* gameObject)
{
	this->selectedObject = gameObject;
}

AGameObject* PrimitiveManager::getSelectedObject()
{
	return this->selectedObject;
}


