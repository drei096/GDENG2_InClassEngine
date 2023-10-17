#include "TransformComponent.h"

#include "AComponent.h"
#include "AGameObject.h"
#include "BaseComponentSystem.h"
#include "TransformSystem.h"


TransformComponent::TransformComponent(String name, AGameObject* owner) : AComponent(name, ComponentType::Transform, owner)
{
	BaseComponentSystem::GetInstance()->GetTransformSystem()->RegisterComponent(this);
}

TransformComponent::~TransformComponent()
{
	BaseComponentSystem::GetInstance()->GetTransformSystem()->UnRegisterComponent(this);
	AComponent::~AComponent();
}

void TransformComponent::DetachOwner()
{
	BaseComponentSystem::GetInstance()->GetTransformSystem()->UnRegisterComponent(this);
	AComponent::DetachOwner();
}

void TransformComponent::Perform(float deltaTime)
{
	AComponent::Perform(deltaTime);
	owner->update(deltaTime);
}
