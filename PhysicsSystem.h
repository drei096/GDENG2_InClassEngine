#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>


using namespace reactphysics3d;

class PhysicsComponent;
class PhysicsSystem
{
public:
	typedef std::string String;
	typedef std::unordered_map <String, PhysicsComponent*> componentTable;
	typedef std::vector<PhysicsComponent*> componentList;


	PhysicsSystem();
	~PhysicsSystem();

	void RegisterComponent(PhysicsComponent* component);
	void UnRegisterComponent(PhysicsComponent* component);
	void UnRegisterComponentByName(String name);
	PhysicsComponent* FindComponentByName(String name);
	componentList GetAllComponents();

	void UpdateAllComponents();
	PhysicsWorld* GetPhysicsWorld();
	PhysicsCommon* GetPhysicsCommon();

private:
	PhysicsCommon* physicsCommon = nullptr;
	PhysicsWorld* physicsWorld = nullptr;

	componentTable _componentTable;
	componentList _componentList;
};

