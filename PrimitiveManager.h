#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "CubePrimitive.h"
#include "PlanePrimitive.h"
#include "LinePrimitive.h"
#include "ShaderCollection.h"

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
		SPHERE,
		LINE,
		MESH,
		PHYSICS_CUBE,
		PHYSICS_PLANE,
	};

	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);

	List getAllObjects();
	int getActiveObjectsCount();

	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight);

	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type, ShaderTypes shaderType);

	//NEW! CREATE PRIMS AT A SPECIFIED POINT
	void createObjectAtPoint(PrimitiveType type, Vector3D forLine_origin, Vector3D point, ShaderTypes shaderType);
	void createObjectAtPoint(PrimitiveType type, Vector3D point, ShaderTypes shaderType);
	void createObjectAtPoint(PrimitiveType type, float x, float y, float z, ShaderTypes shaderType);

	//NEW! CREATE PRIMS WITH TRANSFORMATIONS
	void createObjectWithTransformations(PrimitiveType type, ShaderTypes shaderType, Vector3D translateBy, Vector3D scaleBy, Vector3D rotateBy);

	//NEW! CREATE MESHES
	void createTeapot(ShaderTypes shaderType);
	void createBunny(ShaderTypes shaderType);
	void createArmadillo(ShaderTypes shaderType);
	AGameObject* createTeapot(ShaderTypes shaderType, Vector3D pos);
	AGameObject* createBunny(ShaderTypes shaderType, Vector3D pos);
	AGameObject* createArmadillo(ShaderTypes shaderType, Vector3D pos);
	AGameObject* createStatue(ShaderTypes shaderType, Vector3D pos);
	AGameObject* createEarth(ShaderTypes shaderType, Vector3D pos);
	AGameObject* createScene(ShaderTypes shaderType, Vector3D pos);
	AGameObject* createSphere(ShaderTypes shaderType, Vector3D pos);
	AGameObject* createCapsule(ShaderTypes shaderType, Vector3D pos);


	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);
	
	

private:
	HashTable gameObjectMap;
	List gameObjectList;

	AGameObject* selectedObject = nullptr;

private:
	friend class GraphicsEngine;
};
