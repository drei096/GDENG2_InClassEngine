#pragma once
#include "ResourceManager.h"

class TextureManager : public ResourceManager
{
public:
	TextureManager();
	~TextureManager();

	Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;
	Texture* createTextureFromFile(const wchar_t* file_path);
};

