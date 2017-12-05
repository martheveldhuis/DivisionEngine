#ifndef DIVISION_D3D9TEXTURE_H
#define DIVISION_D3D9TEXTURE_H

#include "Resource.h"
#include <d3d9.h>

namespace Division
{
	class D3D9Texture : public Resource
	{
	public:
		D3D9Texture(LPDIRECT3DTEXTURE9);
		~D3D9Texture();
		LPDIRECT3DTEXTURE9 getTextureData();
	private:
		LPDIRECT3DTEXTURE9 textureData_ = NULL;
	};
}

#endif