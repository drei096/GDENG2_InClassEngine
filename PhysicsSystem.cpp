#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include <iostream>
#include "EngineTime.h"


PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
}

PhysicsSystem::~PhysicsSystem()
{
	delete physicsCommon;
}

void PhysicsSystem::RegisterComponent(PhysicsComponent* component)
{
	_componentTable[component->GetName()] = component;
	_componentList.push_back(component);
}

void PhysicsSystem::UnRegisterComponent(PhysicsComponent* component)
{
	if (_componentTable[component->GetName()] != nullptr)
	{
		_componentTable.erase(component->GetName());
		int index = -1;
		for (int i = 0; i < _componentList.size(); ++i)
		{
			if (_componentList[i] == component)
			{
				index = i;
				break;
			}
		}

		if (index != -1)
		{
			_componentList.erase(_componentList.begin() + index);
		}
	}
	else
	{
		std::cout << "Component " << component->GetName() << " not registered in physics component. \n";
	}
}

void PhysicsSystem::UnRegisterComponentByName(String name)
{
	if (_componentTable[name] != nullptr)
	{
		UnRegisterComponent(_componentTable[name]);
	}
}

PhysicsComponent* PhysicsSystem::FindComponentByName(String name)
{
	if (_componentTable[name] == nullptr)
	{
		std::cout << "Component " << name << " not registered in physics component.\n";
	}

	return _componentTable[name];
}

PhysicsSystem::componentList PhysicsSystem::GetAllComponents()
{
	return _componentList;
}

void PhysicsSystem::UpdateAllComponents()
{
	// do not update during first frame. Delta time is still 0.
	if (EngineTime::getDeltaTime() > 0)
	{
		// update physics world
		physicsWorld->update(EngineTime::getDeltaTime());
		for (int i = 0; i < _componentList.size(); ++i)
		{
			_componentList[i]->Perform(EngineTime::getDeltaTime());
		}
	}
}

PhysicsWorld* PhysicsSystem::GetPhysicsWorld()
{
	return physicsWorld;
}

PhysicsCommon* PhysicsSystem::GetPhysicsCommon()
{
	return physicsCommon;
}
