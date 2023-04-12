#pragma once
#include <iostream>
#include "IWorkerAction.h"
#include "BNS_EnumHandler.h"
#include "Vector3D.h"

class IExecutionEvent;
class ObjectScene;
class ObjectLoader : public IWorkerAction
{
public:
	ObjectLoader(ObjectScene* sceneRef, BNS_MeshType meshType, Vector3D pos, IExecutionEvent* executionEvent);
	~ObjectLoader();

private:
	void onStartTask() override;

	ObjectScene* sceneRef;
	BNS_MeshType meshType;
	Vector3D pos;
	IExecutionEvent* execEvent;

};