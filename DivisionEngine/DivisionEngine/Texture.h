#ifndef DIVISION_TEXTURE_H
#define DIVISION_TEXTURE_H

#include "Resource.h"
#include <d3d9.h>

namespace Division
{
	class Texture : public Resource
	{
	public:
		Texture(LPDIRECT3DTEXTURE9);
		~Texture();
		void* getResourceData();
	private:
		LPDIRECT3DTEXTURE9 textureData_ = NULL;
	};
}

#endif