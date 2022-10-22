#pragma once
#include "Camera.h"

class ViewportCameraManager
{
public:
	static ViewportCameraManager* getInstance();
	static void init();
	static void destroy();
	~ViewportCameraManager();

	void update(); 

	Matrix4x4 getSceneCameraViewMatrix();

private:
	ViewportCameraManager();
	
	ViewportCameraManager(ViewportCameraManager const&) {};             // copy constructor is private
	ViewportCameraManager& operator=(ViewportCameraManager const&) {};  // assignment operator is private*/
	static ViewportCameraManager* sharedInstance;

	Camera* sceneCamera;

};

