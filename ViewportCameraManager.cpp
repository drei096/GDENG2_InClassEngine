#include "ViewportCameraManager.h"
#include "EngineTime.h"

ViewportCameraManager* ViewportCameraManager::sharedInstance = NULL;

ViewportCameraManager* ViewportCameraManager::getInstance()
{
    return sharedInstance;
}

void ViewportCameraManager::init()
{
    sharedInstance = new ViewportCameraManager();
}

void ViewportCameraManager::destroy()
{
    sharedInstance->sceneCamera->~Camera();
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

Matrix4x4 ViewportCameraManager::GetSceneCameraMatrix()
{
    return this->sceneCamera->getMatrix();
}

Matrix4x4 ViewportCameraManager::GetSceneCameraProjectionMatrix()
{
    return this->sceneCamera->getCamProjMatrix();
}

Camera* ViewportCameraManager::getSceneCamera()
{
    return this->sceneCamera;
}

ViewportCameraManager::ViewportCameraManager()
{
    this->sceneCamera = new Camera("SceneCamera");
}
ViewportCameraManager::~ViewportCameraManager()
{
    delete this->sceneCamera;
}

