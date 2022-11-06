#include "ResourceManager.h"
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

Resource* ResourceManager::createResourceFromFile(const wchar_t* file_path)
{
	std::wstring full_path = std::experimental::filesystem::absolute(file_path);

	auto it = m_resource_map.find(full_path);
	if(it !=  m_resource_map.end())
	{
		return it->second;
	}

	Resource* raw_res = this->createResourceFromFileConcrete(full_path.c_str());
	if(raw_res)
	{
		Resource* res(raw_res);
		m_resource_map[full_path] = res;
		return res;
	}

	return nullptr;
}
