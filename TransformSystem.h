#pragma once
#include <string>
#include <unordered_map>

class TransformComponent;
class TransformSystem
{
public:
	typedef std::string String;
	typedef std::unordered_map<String, TransformComponent*> componentTable;
	typedef std::vector<TransformComponent*> componentList;


	TransformSystem();
	~TransformSystem();

	void RegisterComponent(TransformComponent* component);
	void UnRegisterComponent(TransformComponent* component);
	void UnRegisterComponentByName(String name);
	TransformComponent* FindComponentByName(String name);
	componentList GetAllComponents();

	void UpdateAllComponents();


private:
	componentTable _componentTable;
	componentList _componentList;
};

