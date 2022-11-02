#include "ShaderCollection.h"

ShaderCollection* ShaderCollection::GetInstance()
{
	static ShaderCollection shaderCollection;
	return &shaderCollection;
}

void ShaderCollection::LoadAllShaders()
{
	shaderHashTable[VERTEX_SHADER_ALBEDO] = L"AlbedoVertexShader.hlsl";
	shaderHashTable[PIXEL_SHADER_ALBEDO] = L"AlbedoPixelShader.hlsl";
	shaderHashTable[VERTEX_SHADER_LERPING_ALBEDO] = L"LerpingAlbedoVertexShader.hlsl";
	shaderHashTable[PIXEL_SHADER_LERPING_ALBEDO] = L"LerpingAlbedoPixelShader.hlsl";
}

void ShaderCollection::getShadersByType(ShaderTypes shaderType, LPCWSTR* vertexShaderName, LPCWSTR* pixelShaderName)
{
	switch (shaderType)
	{
	case ALBEDO:
		*vertexShaderName = shaderHashTable[VERTEX_SHADER_ALBEDO];
		*pixelShaderName = shaderHashTable[PIXEL_SHADER_ALBEDO];
		break;

	case LERPING_ALBEDO:
		*vertexShaderName = shaderHashTable[VERTEX_SHADER_LERPING_ALBEDO];
		*pixelShaderName = shaderHashTable[PIXEL_SHADER_LERPING_ALBEDO];
		break;
	}
}