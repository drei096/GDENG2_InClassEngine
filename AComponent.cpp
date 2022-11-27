#include "AComponent.h"

AComponent::AComponent(String name, ComponentType type, AGameObject* owner)
{
    this->name = name;
    this->owner = owner;
    this->type = type;
}

AComponent::~AComponent()
{
    owner = nullptr;
    type = ComponentType::NotSet;
}

void AComponent::AttachOwner(AGameObject* owner)
{
    this->owner = owner;
}

void AComponent::DetachOwner()
{
    //if object owner gets detached. then component must also be deleted.
    owner = NULL;
}

AGameObject* AComponent::GetOwner()
{
    return owner;
}

AComponent::ComponentType AComponent::GetType()
{
    return type;
}

AComponent::String AComponent::GetName()
{
    return name;
}

void AComponent::Perform(float deltaTime)
{
}