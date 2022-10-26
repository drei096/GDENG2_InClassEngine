#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "CubePrimitive.h"
#include "PlanePrimitive.h"

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
	int getActiveObjectsCount();

	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight);

	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);

	//NEW! CREATE PRIMS AT A SPECIFIED POINT
	void createObjectAtPoint(PrimitiveType type, Vector3D point);
	void createObjectAtPoint(PrimitiveType type, float x, float y, float z);

	//NEW! CREATE PRIMS WITH TRANSFORMATIONS
	void createObjectWithTransformations(PrimitiveType type, Vector3D translateBy, Vector3D scaleBy, Vector3D rotateBy);

	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);
	
	

private:
	HashTable gameObjectMap;
	List gameObjectList;

	AGameObject* selectedObject = nullptr;

private:
	friend class GraphicsEngine;
};
