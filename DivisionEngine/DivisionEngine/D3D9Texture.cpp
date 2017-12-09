#include "D3D9Texture.h"

namespace Division
{
	D3D9Texture::D3D9Texture(LPDIRECT3DTEXTURE9 textureData) : textureData_(textureData)
	{
	}

	D3D9Texture::~D3D9Texture()
	{
	}

	LPDIRECT3DTEXTURE9 D3D9Texture::getTextureData()
	{
		return textureData_;
	}
}