#ifndef DIVISION_TERRAIN_H
#define DIVISION_TERRAIN_H

#include "D3D9Mesh.h"
#include "Renderer.h"
#include "D3D9Texture.h"
#include "Entity.h"

namespace Division
{
	class Terrain : public Entity
	{
	public:
		Terrain(ResourceManager*, DivisionVertex vertices[], int, int);
		~Terrain();
		void render(Renderer* renderer);
		int generateIndices(int** ppIndices, int verticesAlongWidth, int verticesAlongLength);
	private:
		D3D9Texture* texture_ = NULL; // texture
		DivisionVertex* vertices_;
		int vertexCount_ = 0;
		int* indices_ = NULL;
		DWORD indexCount_ = 0;
		LPDIRECT3DDEVICE9 direct3Ddevice_ = NULL; // device
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL; // buffer
		LPDIRECT3DINDEXBUFFER9 indexBuffer_ = NULL; // Buffer to hold indices
	};
}

#endif