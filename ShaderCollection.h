#pragma once
#include <unordered_map>
#include <Windows.h>

enum ShaderTypes
{
	ALBEDO,
	LERPING_ALBEDO,
	FLAT_TEXTURED,
	MESH_TEXTURED,
};

enum ShaderTypesIndiv
{
	VERTEX_SHADER_ALBEDO,
	PIXEL_SHADER_ALBEDO,
	VERTEX_SHADER_LERPING_ALBEDO,
	PIXEL_SHADER_LERPING_ALBEDO,
	VERTEX_SHADER_FLAT_TEXTURED,
	PIXEL_SHADER_FLAT_TEXTURED,
	VERTEX_SHADER_MESH_TEXTURED,
	PIXEL_SHADER_MESH_TEXTURED,
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