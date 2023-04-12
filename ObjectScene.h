#pragma once
#include "AScene.h"
#include "PrimitiveManager.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

#include "IExecutionEvent.h"

class ObjectScene : public AScene, public IExecutionEvent
{
public:
	ObjectScene(std::string name, int index);
	~ObjectScene();

public:
	// Inherited via AScene
	virtual void loadObjects() = 0;
	virtual void unloadObjects() override;
	virtual void toggleObjects() override;

	// Inherited via IExecutionEvent
	virtual void onFinishedExecution() override;

public:
	void addObject(AGameObject* object);

public:
	int countLoaded = 0;
	int maxObjects = 0;
	bool hasLoaded = false;

protected:
	std::vector<Vector3D> posList;
	std::vector<Vector3D> occupiedList;
	std::vector<AGameObject*> objectList;
};

