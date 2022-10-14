#pragma once
#include "Camera.h"

class ViewportCameraManager
{
public:
	static ViewportCameraManager* getInstance();
	static void initialize();
	static void destroy();

	void update(); //TODO: Game object manager should perform update of all game objects

	Matrix4x4 getSceneCameraViewMatrix();

private:
	ViewportCameraManager();
	~ViewportCameraManager();
	ViewportCameraManager(ViewportCameraManager const&) {};             // copy constructor is private
	ViewportCameraManager& operator=(ViewportCameraManager const&) {};  // assignment operator is private*/
	static ViewportCameraManager* sharedInstance;

	Camera* sceneCamera;

};

