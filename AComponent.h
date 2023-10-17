#pragma once

#include <memory>
#include <string>

class AGameObject;
class AComponent
{
public:
	typedef std::string String;

	enum ComponentType
	{
		NotSet = -1,
		Script = 0,
		Renderer = 1,
		Input = 2,
		Physics = 3,
		Transform = 4,
	};

	AComponent(String name, ComponentType type, AGameObject* owner);
	~AComponent();

	void AttachOwner(AGameObject* owner);
	virtual void DetachOwner();
	AGameObject* GetOwner();
	ComponentType GetType();
	String GetName();

	virtual void Perform(float deltaTime); // performs the associated action.

protected:
	AGameObject* owner;
	ComponentType type;
	String name;
};

