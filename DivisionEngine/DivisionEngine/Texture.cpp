#include "Texture.h"

namespace Division
{
	Texture::Texture(LPDIRECT3DTEXTURE9 textureData) : textureData_(textureData)
	{
	}

	Texture::~Texture()
	{
	}

	void* Texture::getResourceData()
	{
		return (void*)textureData_;
	}
}