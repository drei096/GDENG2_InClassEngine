#pragma once

#include "ResourceManager.h"

class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();

	Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;
	Mesh* createMeshFromFile(const wchar_t* file_path);
};

