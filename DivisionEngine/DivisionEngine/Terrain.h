#ifndef DIVISION_TERRAIN_H
#define DIVISION_TERRAIN_H

#include "D3D9Mesh.h"
#include "Renderer.h"
#include "Texture.h"

namespace Division
{
	class Terrain
	{
	public:
		Terrain(CUSTOMVERTEX vertices[], int vertexCount);
		~Terrain();
		void render(Renderer* renderer);
		int generateIndices(int** ppIndices, int verticesAlongWidth, int verticesAlongLength);
	private:
		Texture* texture_ = NULL; // texture
		CUSTOMVERTEX* vertices_;
		int vertexCount_ = 0;
		int* indices_ = NULL;
		DWORD indexCount_ = 0;
		LPDIRECT3DDEVICE9 direct3Ddevice_ = NULL; // device
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL; // buffer
		LPDIRECT3DINDEXBUFFER9 indexBuffer_ = NULL; // Buffer to hold indices
	};
}

#endif