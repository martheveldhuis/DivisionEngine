#ifndef DIVISION_SKYBOX_H
#define DIVISION_SKYBOX_H

#include "D3D9Mesh.h"
#include "D3D9Texture.h"
#include "Entity.h"

namespace Division
{
	/**
	    The skybox cube surrounding the active camera to give the illusion of a
		sky being rendered beyond other entities.
		The skybox is rendered by disabling the z-buffer before rendering the
		cube, this way the skybox is always rendered behind other entities.
	*/
	class D3D9SkyBox : public Entity
	{
	public:
		/**
			Creates a skybox.
			@param rm The resource manager to get textures and meshes from.
			@param side The length of the sides of the cube.
		*/
		D3D9SkyBox(ResourceManager* rm, float side);
		~D3D9SkyBox();
		void render(Renderer* renderer);
		/**
			Get the texture from the resource manager and set it on the skybox.
			@param textureName The texture to load.
		*/
		void setTexture(std::string textureName);
	private:
		Resource* texture_ = NULL;
		DivisionVertex* vertices_;
		int vertexCount_ = 0;
		int* indices_;
		DWORD indexCount_ = 0;
		LPDIRECT3DDEVICE9 direct3Ddevice_ = NULL;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL;
		LPDIRECT3DINDEXBUFFER9 indexBuffer_ = NULL;
	};
}

#endif