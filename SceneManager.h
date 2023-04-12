#pragma once
#include "AScene.h"
#include <vector>

class ThreadPool;
class IETSemaphore;
class SceneManager
{
private:
	SceneManager();
	~SceneManager();
	SceneManager(SceneManager const&) {}; // copy constructor is private
	SceneManager& operator=(SceneManager const&) {}; // assignment operator is private

public:
	void addScene(AScene* scene);
	void initializeScenes();
	std::vector<AScene*> &getSceneList();
	ThreadPool* getThreadPool();

	void loadSceneByIndex(int index);
	void loadAllScenes();

	void unloadSceneByIndex(int index);
	void unloadAllScenes();

	void toggleSceneByIndex(int index);
	void toggleAllScenes();

public:
	static void create();
	static void release();
	static SceneManager* Instance();

public:
	IETSemaphore* sceneLoadSem;
	IETSemaphore* objLoadSem;
	IETSemaphore* objmutex;

private:
	std::vector<AScene*> sceneList;

	ThreadPool* threadPool;

private:
	static SceneManager* sharedInstance;
};

