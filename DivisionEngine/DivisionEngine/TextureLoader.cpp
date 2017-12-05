#include "TextureLoader.h"

namespace Division
{
	TextureLoader::TextureLoader()
	{
	}



	TextureLoader::~TextureLoader()
	{
	}



	Resource* TextureLoader::getResource(std::string textureFile, void* d3dDevice)
	{
		// TODO: remove this line
		LPDIRECT3DDEVICE9 g_pd3dDevice = static_cast<LPDIRECT3DDEVICE9>(d3dDevice);

		LPDIRECT3DTEXTURE9 textureData = NULL;

		HRESULT result = D3DXCreateTextureFromFile(g_pd3dDevice,
			textureFile.c_str(),
			&textureData);
		if (FAILED(result))
		{
			std::string prefixedTextureFile = "..\\" + textureFile;

			if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice,
				prefixedTextureFile.c_str(),
				&textureData)))
			{
				// TODO: Log that this failed.
			}
		}

		return new D3D9Texture(textureData);
	}
}
