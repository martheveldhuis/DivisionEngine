#ifndef DIVISION_TEXTURE_H
#define DIVISION_TEXTURE_H

#include "Resource.h"
#include <d3d9.h>

namespace Division {
	class Texture
	{
	public:
		Texture();
		~Texture();
	private:
		LPDIRECT3DTEXTURE9	textureData_ = NULL;
	};
}
#endif