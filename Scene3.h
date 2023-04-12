#pragma once
#include "ObjectScene.h"

class Scene3 : public ObjectScene
{
public:
	Scene3(std::string name, int index);
	~Scene3();

public:
	// Inherited via ObjectScene
	virtual void loadObjects() override;
};

