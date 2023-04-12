#pragma once
#include <string>
#include <vector>
#include "Vector3D.h"
#include "AGameObject.h"

class AScene
{
public:
	AScene(std::string name, int index);
	~AScene();

	virtual void loadObjects() = 0;
	virtual void unloadObjects() = 0;
	virtual void toggleObjects() = 0;

private:
	std::string name;
	int index;
};

