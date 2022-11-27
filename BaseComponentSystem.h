#pragma once
#include <string>


class PhysicsSystem;


class BaseComponentSystem
{
public:
	typedef std::string String;

	static BaseComponentSystem* GetInstance();
	static void Initialize();
	static void Destroy();

	PhysicsSystem* GetPhysicsSystem();

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&); // copy constructor is private
	BaseComponentSystem& operator=(BaseComponentSystem const&) {}; // assignment operator is private
	static  BaseComponentSystem* sharedInstance;

	PhysicsSystem* physicsSystem;
};

