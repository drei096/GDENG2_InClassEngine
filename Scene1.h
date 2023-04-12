#pragma once
#include "ObjectScene.h"

class Scene1 : public ObjectScene
{
public:
	Scene1(std::string name, int index);
	~Scene1();

public:
	// Inherited via ObjectScene
	virtual void loadObjects() override;
};

