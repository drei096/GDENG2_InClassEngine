#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(String name, AGameObject* owner);
	~PhysicsComponent();
	// update rigidBody
	void UpdateRigidBody();
	// executes the physics system per frame
	void Perform(float deltaTime) override;
	RigidBody* GetRigidBody();

private:
	float mass = 1000.0f; // in kilograms
	RigidBody* rigidBody;
	BoxShape* boxShape = nullptr;
};

