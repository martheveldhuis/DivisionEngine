#ifndef DIVISION_SKYBOX_H
#define DIVISION_SKYBOX_H

#include "D3D9Mesh.h"
#include "Renderer.h"
#include "D3D9Texture.h"
#include "Entity.h"

namespace Division
{
	struct SkyBoxVertex
	{
		float x, y, z;
		float u, v;
	};

	class SkyBox : public Entity
	{
	public:
		SkyBox(ResourceManager*, SkyBoxVertex vertices[]);
		~SkyBox();
		void render(Renderer* renderer);
		void setTexture(std::string);
	private:
		D3D9Texture* texture_ = NULL; // texture
		SkyBoxVertex* vertices_;
		int vertexCount_ = 0;
		int* indices_;
		DWORD indexCount_ = 0;
		LPDIRECT3DDEVICE9 direct3Ddevice_ = NULL; // device
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL; // buffer
		LPDIRECT3DINDEXBUFFER9 indexBuffer_ = NULL; // Buffer to hold indices
	};
}

#endif