#include "VertexBuffer.h"
#include "RenderingSystem.h"

VertexBuffer::VertexBuffer(RenderingSystem* system) : m_renderingSystem(system), m_input_layout(0), m_buffer(0)
{
}

VertexBuffer::~VertexBuffer()
{
}

bool VertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader, ShaderTypes shaderType)
{
	if (m_buffer)m_buffer->Release();
	if (m_input_layout)m_input_layout->Release();

	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = size_vertex * size_list;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	m_size_vertex = size_vertex;
	m_size_list = size_list;

	if(FAILED(m_renderingSystem->d3d11_device->CreateBuffer(&buffer_desc, &init_data, &m_buffer)))
	{
		return false;
	}




	if(shaderType == ShaderTypes::ALBEDO)
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			//SEMANTIC NAME, SEMANTIC INDEX, FORMAT, INPUT SLOT, ALIGNED BYTE OFFSET, INPUT SLOT CLASS, INSTANCE DATA STEP RATE
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		UINT size_layout = ARRAYSIZE(layout);

		if (FAILED(m_renderingSystem->d3d11_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_input_layout)))
		{
			return false;
		}
	}
	else if (shaderType == ShaderTypes::LERPING_ALBEDO)
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			//SEMANTIC NAME, SEMANTIC INDEX, FORMAT, INPUT SLOT, ALIGNED BYTE OFFSET, INPUT SLOT CLASS, INSTANCE DATA STEP RATE
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "COLOR", 1,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 24,D3D11_INPUT_PER_VERTEX_DATA ,0 }
		};

		UINT size_layout = ARRAYSIZE(layout);

		if (FAILED(m_renderingSystem->d3d11_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_input_layout)))
		{
			return false;
		}
	}
	else if (shaderType == ShaderTypes::FLAT_TEXTURED)
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			//SEMANTIC NAME, SEMANTIC INDEX, FORMAT, INPUT SLOT, ALIGNED BYTE OFFSET, INPUT SLOT CLASS, INSTANCE DATA STEP RATE
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		UINT size_layout = ARRAYSIZE(layout);

		if (FAILED(m_renderingSystem->d3d11_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_input_layout)))
		{
			return false;
		}
	}
	else if (shaderType == ShaderTypes::MESH_TEXTURED)
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			//SEMANTIC NAME, SEMANTIC INDEX, FORMAT, INPUT SLOT, ALIGNED BYTE OFFSET, INPUT SLOT CLASS, INSTANCE DATA STEP RATE
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		UINT size_layout = ARRAYSIZE(layout);

		if (FAILED(m_renderingSystem->d3d11_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_input_layout)))
		{
			return false;
		}
	}
	
	

	return true;
}

bool VertexBuffer::release()
{
	m_input_layout->Release();
	m_buffer->Release();
	delete this;
	return true;
}

UINT VertexBuffer::getSizeVertexList()
{
	return this->m_size_list;
}
