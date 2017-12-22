#ifndef DIVISION_D3D9TEXTURE_H
#define DIVISION_D3D9TEXTURE_H

#include "Resource.h"
#include <d3d9.h>

namespace Division
{
	/**
		Direct 3D texture implementation of a resource.
	*/
	class D3D9Texture : public Resource
	{
	public:
		/**
			Constructs the texture object.
			@param textureData The direct 3d texture data defining the texture.
		*/
		D3D9Texture(LPDIRECT3DTEXTURE9 textureData);
		~D3D9Texture();
		/**
			Gets the direct 3d texture data.
			@returns The direct 3d texture data.
		*/
		LPDIRECT3DTEXTURE9 getTextureData();
	private:
		LPDIRECT3DTEXTURE9 textureData_ = NULL;
	};
}

#endif