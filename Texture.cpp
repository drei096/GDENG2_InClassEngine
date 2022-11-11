#include "Texture.h"
#include <DirectXTex.h>
#include "GraphicsEngine.h"

Texture::Texture(const wchar_t* full_path) : Resource(full_path)
{
	CoInitialize(nullptr);
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(GraphicsEngine::GetInstance()->getRenderingSystem()->d3d11_device, image_data.GetImages(), image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);

		// creates a description for the shaderResourceView
		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		// pass the description data to the shaderResourceView object
		GraphicsEngine::GetInstance()->getRenderingSystem()->d3d11_device->CreateShaderResourceView(m_texture, &desc, &m_shader_res_view);
		
	}
	else
		throw std::exception("Texture not created successfully");

	CoUninitialize();
}

Texture::~Texture()
{
	m_texture->Release();
}

ID3D11ShaderResourceView* Texture::getShaderResourceView()
{
	return m_shader_res_view;
}
