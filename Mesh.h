#pragma once

#include "Resource.h"
#include "AGameObject.h"


class Mesh : public Resource, public AGameObject
{
public:
	Mesh(const wchar_t* full_path, std::string name);
	~Mesh();
	const VertexBuffer* getVertexBuffer();
	const IndexBuffer* getIndexBuffer();

	void update(float deltaTime) override;
	void draw(float width, float height) override;

	void assignTex(Texture* tex);

private:
	friend class DeviceContext;
	Texture* m_tex;
};

