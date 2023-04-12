#include "SceneManager.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "ThreadPool.h"
#include "IETSemaphore.h"

SceneManager* SceneManager::sharedInstance = nullptr;

SceneManager::SceneManager()
{
	this->threadPool = new ThreadPool("MeshLoaderPool", 10);
	this->threadPool->startScheduler();

	this->sceneLoadSem = new IETSemaphore(1);
	this->objLoadSem = new IETSemaphore(10);
	this->objmutex = new IETSemaphore(1);
}

SceneManager::~SceneManager()
{
}

void SceneManager::addScene(AScene* scene)
{
	this->sceneList.push_back(scene);
}

void SceneManager::initializeScenes()
{
	AScene* sceneTemp;

	sceneTemp = new Scene1("Scene1", this->sceneList.size());
	this->addScene(sceneTemp); 
	sceneTemp = new Scene2("Scene2", this->sceneList.size());
	this->addScene(sceneTemp);
	sceneTemp = new Scene3("Scene3", this->sceneList.size());
	this->addScene(sceneTemp);
	sceneTemp = new Scene4("Scene4", this->sceneList.size());
	this->addScene(sceneTemp);
	sceneTemp = new Scene5("Scene5", this->sceneList.size());
	this->addScene(sceneTemp);

	//pre-load all scenes
	loadAllScenes();
}

std::vector<AScene*> &SceneManager::getSceneList()
{
	return this->sceneList;
}

ThreadPool* SceneManager::getThreadPool()
{
	return this->threadPool;
}

void SceneManager::loadSceneByIndex(int index)
{
	if (this->sceneList[index] == NULL)
		return;

	this->sceneList[index]->loadObjects();
}

void SceneManager::loadAllScenes()
{
	if (this->sceneList.empty())
		return;

	for (auto scene : this->sceneList)
		scene->loadObjects();
}

void SceneManager::unloadSceneByIndex(int index)
{
	if (this->sceneList[index] == NULL)
		return;

	this->sceneList[index]->unloadObjects();
}

void SceneManager::unloadAllScenes()
{
	if (this->sceneList.empty())
		return;

	for (auto scene : this->sceneList)
		scene->unloadObjects();
}

void SceneManager::toggleSceneByIndex(int index)
{
	if (this->sceneList[index] == NULL)
		return;

	this->sceneList[index]->toggleObjects();
}

void SceneManager::toggleAllScenes()
{
	if (this->sceneList.empty())
		return;

	for (auto scene : this->sceneList)
		scene->toggleObjects();
}

void SceneManager::create()
{
	if (SceneManager::sharedInstance)
		throw std::exception("Scene Manager already created");
	else
	{
		SceneManager::sharedInstance = new SceneManager();
	}
}

void SceneManager::release()
{
	if (!SceneManager::sharedInstance)
		return;
	delete SceneManager::sharedInstance;
}

SceneManager* SceneManager::Instance()
{
	return sharedInstance;
}
