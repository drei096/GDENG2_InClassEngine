#pragma once
#include "ObjectScene.h"

class Scene2 : public ObjectScene
{
public:
	Scene2(std::string name, int index);
	~Scene2();

public:
	// Inherited via ObjectScene
	virtual void loadObjects() override;
};
