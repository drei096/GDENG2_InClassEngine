#include "ViewportCameraManager.h"
#include "EngineTime.h"

ViewportCameraManager* ViewportCameraManager::sharedInstance = NULL;

ViewportCameraManager* ViewportCameraManager::getInstance()
{
    return sharedInstance;
}

void ViewportCameraManager::initialize()
{
    sharedInstance = new ViewportCameraManager();
}

void ViewportCameraManager::destroy()
{
    delete sharedInstance;
}

void ViewportCameraManager::update()
{
    this->sceneCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 ViewportCameraManager::getSceneCameraViewMatrix()
{
    return this->sceneCamera->getViewMatrix();
}

ViewportCameraManager::ViewportCameraManager()
{
    this->sceneCamera = new Camera("SceneCamera");
}
ViewportCameraManager::~ViewportCameraManager()
{
    delete this->sceneCamera;
}

