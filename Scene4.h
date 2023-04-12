#pragma once
#include "ObjectScene.h"

class Scene4 : public ObjectScene
{
public:
	Scene4(std::string name, int index);
	~Scene4();

public:
	// Inherited via ObjectScene
	virtual void loadObjects() override;
};

