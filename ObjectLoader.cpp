#include "ObjectLoader.h"
#include "IETThread.h"
#include "IExecutionEvent.h"
#include "ObjectScene.h"
#include "PrimitiveManager.h"
#include "SceneManager.h"
#include "IETSemaphore.h"

ObjectLoader::ObjectLoader(ObjectScene* sceneRef, BNS_MeshType meshType, Vector3D pos, IExecutionEvent* executionEvent) : sceneRef(sceneRef), meshType(meshType), pos(pos), execEvent(executionEvent)
{

}

ObjectLoader::~ObjectLoader()
{
	std::cout << "Destroying Object Loader" << std::endl;
}

void ObjectLoader::onStartTask()
{
	std::cout << "Running Object Loader" << std::endl;

	SceneManager::Instance()->objLoadSem->acquire(1);

	IETThread::sleep(3000);

	AGameObject* tempRef = nullptr;

	//LOAD OBJECTS HERE
	if (this->meshType == BNS_MeshType::TEAPOT) 
	{
		tempRef = PrimitiveManager::GetInstance()->createTeapot(ShaderTypes::FLAT_TEXTURED, pos);
	}
	else if (this->meshType == BNS_MeshType::STATUE)
	{
		tempRef = PrimitiveManager::GetInstance()->createStatue(ShaderTypes::FLAT_TEXTURED, pos);
	}
	else if (this->meshType == BNS_MeshType::BUNNY)
	{
		tempRef = PrimitiveManager::GetInstance()->createBunny(ShaderTypes::FLAT_TEXTURED, pos);
	}
	else if (this->meshType == BNS_MeshType::ARMADILLO)
	{
		tempRef = PrimitiveManager::GetInstance()->createArmadillo(ShaderTypes::FLAT_TEXTURED, pos);
	}
	else if (this->meshType == BNS_MeshType::SPHERE)
	{
		tempRef = PrimitiveManager::GetInstance()->createSphere(ShaderTypes::FLAT_TEXTURED, pos);
	}
	else if (this->meshType == BNS_MeshType::CAPSULE)
	{
		tempRef = PrimitiveManager::GetInstance()->createCapsule(ShaderTypes::FLAT_TEXTURED, pos);
	}
	else if (this->meshType == BNS_MeshType::EARTH)
	{
		tempRef = PrimitiveManager::GetInstance()->createEarth(ShaderTypes::FLAT_TEXTURED, pos);
	}
	else if (this->meshType == BNS_MeshType::SAMPLE_SCENE)
	{
		tempRef = PrimitiveManager::GetInstance()->createScene(ShaderTypes::FLAT_TEXTURED, pos);
	}

	if (tempRef != nullptr) {
		SceneManager::Instance()->objmutex->acquire();
		sceneRef->addObject(tempRef);
		SceneManager::Instance()->objmutex->release();
		//tempRef->SetActive(false);
	}

	this->execEvent->onFinishedExecution();
	//delete after being done
	delete this;
}