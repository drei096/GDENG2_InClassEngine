#pragma once

#include "AComponent.h"

class TransformComponent : public AComponent
{
public:
	TransformComponent(String name, AGameObject* owner);
	~TransformComponent();
	void DetachOwner() override;
	void Perform(float deltaTime) override;
};

