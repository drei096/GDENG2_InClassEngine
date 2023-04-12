#pragma once
#include "ObjectScene.h"

class Scene5 : public ObjectScene
{
public:
	Scene5(std::string name, int index);
	~Scene5();

public:
	// Inherited via ObjectScene
	virtual void loadObjects() override;
};
