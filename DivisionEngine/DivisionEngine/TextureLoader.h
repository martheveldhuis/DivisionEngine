#ifndef DIVISION_TEXTURELOADER_H
#define DIVISION_TEXTURELOADER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "Win32Window.h"
#include "D3D9Renderer.h"
#include "Texture.h"
#include "ResourceLoader.h"

namespace Division
{
	class TextureLoader : public ResourceLoader
	{
	public:
		TextureLoader();
		~TextureLoader();
		static Resource* getResource(std::string, void*);
	};
}

#endif // !DIVISION_TEXTURELOADER_H