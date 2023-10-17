#include "TransformSystem.h"

#include "EngineTime.h"
#include "TransformComponent.h"

TransformSystem::TransformSystem()
{
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::RegisterComponent(TransformComponent* component)
{
	_componentTable[component->GetName()] = component;
	_componentList.push_back(component);
}

void TransformSystem::UnRegisterComponent(TransformComponent* component)
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
		std::cout << "Component " << component->GetName() << " not registered in transform component. \n";
	}
}

void TransformSystem::UnRegisterComponentByName(String name)
{
	if (_componentTable[name] != nullptr)
	{
		UnRegisterComponent(_componentTable[name]);
	}
}

TransformComponent* TransformSystem::FindComponentByName(String name)
{
	if (_componentTable[name] == nullptr)
	{
		std::cout << "Component " << name << " not registered in transform component.\n";
	}

	return _componentTable[name];
}

TransformSystem::componentList TransformSystem::GetAllComponents()
{
	return _componentList;
}

void TransformSystem::UpdateAllComponents()
{
	// do not update during first frame. Delta time is still 0.
	if (EngineTime::getDeltaTime() > 0.0)
	{
		for (int i = 0; i < _componentList.size(); ++i)
		{
			_componentList[i]->Perform((float)EngineTime::getDeltaTime());
		}
	}
}
