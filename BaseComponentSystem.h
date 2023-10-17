#pragma once
#include <string>

class TransformSystem;
class PhysicsSystem;


class BaseComponentSystem
{
public:
	typedef std::string String;

	static BaseComponentSystem* GetInstance();
	static void Initialize();
	static void Destroy();

	PhysicsSystem* GetPhysicsSystem();
	TransformSystem* GetTransformSystem();

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&); // copy constructor is private
	BaseComponentSystem& operator=(BaseComponentSystem const&) {}; // assignment operator is private
	static  BaseComponentSystem* sharedInstance;

	PhysicsSystem* physicsSystem;
	TransformSystem* transformSystem;
};

