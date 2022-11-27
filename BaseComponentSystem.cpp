#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem* BaseComponentSystem::GetInstance()
{
	return sharedInstance;
}

void BaseComponentSystem::Initialize()
{
	sharedInstance = new BaseComponentSystem();
}

void BaseComponentSystem::Destroy()
{
	delete sharedInstance;
}

PhysicsSystem* BaseComponentSystem::GetPhysicsSystem()
{
	return physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
	physicsSystem = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem()
{
	delete physicsSystem;
}