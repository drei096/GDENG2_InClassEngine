#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "CubePrimitive.h"

class GraphicsEngine;

class PrimitiveManager
{
public:
	static PrimitiveManager* GetInstance();

	typedef std::string String;
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	enum PrimitiveType {
		CUBE,
		PLANE,
		SPHERE
	};

	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);
	List getAllObjects();
	int activeObjects();
	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);
	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();

	

private:
	HashTable gameObjectMap;
	List gameObjectList;

	AGameObject* selectedObject = nullptr;

private:
	friend class GraphicsEngine;
};
