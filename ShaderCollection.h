#pragma once
#include <unordered_map>
#include <Windows.h>

enum ShaderTypes
{
	ALBEDO,
	LERPING_ALBEDO
};

enum ShaderTypesIndiv
{
	VERTEX_SHADER_ALBEDO,
	PIXEL_SHADER_ALBEDO,
	VERTEX_SHADER_LERPING_ALBEDO,
	PIXEL_SHADER_LERPING_ALBEDO,
};

class ShaderCollection
{
public:
	static ShaderCollection* GetInstance();


public:
	std::unordered_map<ShaderTypesIndiv, LPCWSTR> shaderHashTable;



public:
	void LoadAllShaders();
	void getShadersByType(ShaderTypes shaderType, LPCWSTR* vertexShaderName, LPCWSTR* pixelShaderName);
};