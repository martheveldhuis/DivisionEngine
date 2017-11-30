#ifndef DIVISION_TEXTURELOADER_H
#define DIVISION_TEXTURELOADER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

namespace Division
{
	class TextureLoader
	{
	public:
		TextureLoader();
		~TextureLoader();
		LPDIRECT3DTEXTURE9 getTexture(std::string);
	};
}

#endif // !DIVISION_TEXTURELOADER_H