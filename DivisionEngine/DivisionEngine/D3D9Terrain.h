#ifndef DIVISION_TERRAIN_H
#define DIVISION_TERRAIN_H

#include "D3D9Mesh.h"
#include "Renderer.h"
#include "Resource.h"
#include "Entity.h"

namespace Division
{
	/**
	    A terrain object to render and create terrain.
	*/
	class D3D9Terrain : public Entity
	{
	public:
		/**
		    Create a terrain using the given parameters.
			@param rm The resource manager to get textures and meshes from.
			@param heightmapFile The heightmap file to get heightdata from.
			@param textureFile The texture to use on the terrain.
		*/
		D3D9Terrain(ResourceManager*, std::string heightmapFile, std::string textureFile);
		~D3D9Terrain();
		void render(Renderer* renderer);
		/**
			Get the texture from the resource manager and set it on the terrain.
			@param textureName The texture to load.
		*/
		void setTexture(std::string textureFile);
	private:
		/**
		   Generates indices based on the vertices.
		*/
		int generateIndices(int** ppIndices, int verticesAlongWidth, int verticesAlongLength);
		Resource* texture_ = NULL;
		DivisionVertex* vertices_;
		int vertexCount_ = 0;
		int* indices_ = NULL;
		DWORD indexCount_ = 0;
		LPDIRECT3DDEVICE9 direct3Ddevice_ = NULL;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL;
		LPDIRECT3DINDEXBUFFER9 indexBuffer_ = NULL;
	};
}

#endif