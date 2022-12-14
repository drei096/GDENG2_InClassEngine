#include "IndexBuffer.h"
#include "GraphicsEngine.h"

IndexBuffer::IndexBuffer() :m_buffer(0)
{
}

IndexBuffer::~IndexBuffer()
{
}

bool IndexBuffer::load(void* list_indices, UINT size_list)
{
	if (m_buffer)m_buffer->Release();

	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = 4 * size_list;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_indices;

	m_size_list = size_list;

	if (FAILED(GraphicsEngine::GetInstance()->d3d11_device->CreateBuffer(&buffer_desc, &init_data, &m_buffer)))
	{
		return false;
	}


	return true;
}

bool IndexBuffer::release()
{
	m_buffer->Release();
	delete this;
	return true;
}

UINT IndexBuffer::getSizeIndexList()
{
	return this->m_size_list;
}
