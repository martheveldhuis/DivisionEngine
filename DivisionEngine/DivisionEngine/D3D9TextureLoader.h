#ifndef DIVISION_TEXTURELOADER_H
#define DIVISION_TEXTURELOADER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#include "D3D9Renderer.h"
#include "D3D9Texture.h"
#include "ResourceLoader.h"
#include "LoggerPool.h"

namespace Division
{
	class D3D9TextureLoader : public ResourceLoader
	{
	public:
		D3D9TextureLoader(LPDIRECT3DDEVICE9);
		~D3D9TextureLoader();
		Resource* getResource(std::string);
	private:
		LPDIRECT3DDEVICE9 direct3DDevice_ = NULL;
	};
}

#endif // !DIVISION_TEXTURELOADER_H