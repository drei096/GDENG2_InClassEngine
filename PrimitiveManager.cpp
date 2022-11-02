#include "PrimitiveManager.h"
#include "MathUtils.h"
#include "EngineTime.h"


PrimitiveManager* PrimitiveManager::GetInstance()
{
	static PrimitiveManager primitiveManager;
	return &primitiveManager;
}


void PrimitiveManager::destroy()
{
	
	for (int i = 0; i < GetInstance()->gameObjectList.size(); i++)
	{
		GetInstance()->gameObjectList[i]->release();
		delete GetInstance()->gameObjectList[i];
	}
	

	GetInstance()->gameObjectMap.clear();
	GetInstance()->gameObjectList.clear();
	
}

AGameObject* PrimitiveManager::findObjectByName(std::string name)
{
	if (this->gameObjectMap[name] != NULL) 
	{
		return this->gameObjectMap[name];
	}
	else 
	{
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

PrimitiveManager::List PrimitiveManager::getAllObjects()
{
	return this->gameObjectList;
}

int PrimitiveManager::getActiveObjectsCount()
{
	return gameObjectList.size();
}

void PrimitiveManager::updateAll()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) 
	{
		if (this->gameObjectList[i]->isEnabled()) 
		{
			this->gameObjectList[i]->update(EngineTime::getDeltaTime());

			//to possibly add: update fxns of each obj components
		}
	}
}

void PrimitiveManager::renderAll(int viewportWidth, int viewportHeight)
{
	for (int i = 0; i < this->gameObjectList.size(); i++) 
	{
		if (this->gameObjectList[i]->isEnabled()) 
		{
			this->gameObjectList[i]->draw(viewportWidth, viewportHeight);
		}
	}
}

void PrimitiveManager::addObject(AGameObject* gameObject)
{
	// IF THE CREATED GAME OBJECT HAS A DUPLICATE, REVISE ITS NAME
	if (this->gameObjectMap[gameObject->getName()] != NULL)
	{
		int count = 1;
		String revisedString = gameObject->getName() + " " + "(" + std::to_string(count) + ")";

		while (this->gameObjectMap[revisedString] != NULL) 
		{
			count++;
			revisedString = gameObject->getName() + " " + "(" + std::to_string(count) + ")";
		}
		//std::cout << "Duplicate found. New name is: " << revisedString << "\n";

		gameObject->name = revisedString;
		this->gameObjectMap[revisedString] = gameObject;
	}
	// ELSE, PUT THE GAME OBJECT IN HASH TABLE
	else 
	{
		this->gameObjectMap[gameObject->getName()] = gameObject;
	}

	//ADD IT ALSO TO THE LIST
	this->gameObjectList.push_back(gameObject);
}

void PrimitiveManager::createObject(PrimitiveType type, ShaderTypes shaderType)
{
	if (type == PrimitiveType::CUBE) 
	{
		CubePrimitive* cube = new CubePrimitive("Cube", shaderType);
		this->addObject(cube);
	}

	
	if (type == PrimitiveType::PLANE) 
	{
		PlanePrimitive* plane = new PlanePrimitive("Plane", shaderType);
		this->addObject(plane);
	}
	
}

void PrimitiveManager::createObjectAtPoint(PrimitiveType type, Vector3D point, ShaderTypes shaderType)
{
	if (type == PrimitiveType::CUBE)
	{
		CubePrimitive* cube = new CubePrimitive("Cube", shaderType);
		cube->setPosition(point);
		this->addObject(cube);
	}


	if (type == PrimitiveType::PLANE)
	{
		PlanePrimitive* plane = new PlanePrimitive("Plane", shaderType);
		plane->setPosition(point);
		this->addObject(plane);
	}
}

void PrimitiveManager::createObjectAtPoint(PrimitiveType type, float x, float y, float z, ShaderTypes shaderType)
{
	if (type == PrimitiveType::CUBE)
	{
		CubePrimitive* cube = new CubePrimitive("Cube", shaderType);
		cube->setPosition(x, y, z);
		this->addObject(cube);
	}


	if (type == PrimitiveType::PLANE)
	{
		PlanePrimitive* plane = new PlanePrimitive("Plane", shaderType);
		plane->setPosition(x, y, z);
		this->addObject(plane);
	}
}

void PrimitiveManager::createObjectWithTransformations(PrimitiveType type, ShaderTypes shaderType, Vector3D translateBy, Vector3D scaleBy, Vector3D rotateBy)
{
	if (type == PrimitiveType::CUBE)
	{
		CubePrimitive* cube = new CubePrimitive("Cube", shaderType);
		cube->setPosition(translateBy);
		cube->setScale(scaleBy);
		cube->setRotation(rotateBy);
		this->addObject(cube);
	}


	if (type == PrimitiveType::PLANE)
	{
		PlanePrimitive* plane = new PlanePrimitive("Plane", shaderType);
		plane->setPosition(translateBy);
		plane->setScale(scaleBy);
		plane->setRotation(rotateBy);
		this->addObject(plane);
	}
}

void PrimitiveManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) 
	{
		if (this->gameObjectList[i] == gameObject) 
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}

	delete gameObject;
}

void PrimitiveManager::deleteObjectByName(std::string name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != NULL) 
	{
		this->deleteObject(object);
	}
}



