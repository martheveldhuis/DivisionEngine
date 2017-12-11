#include "D3D9TextureLoader.h"

namespace Division
{
	D3D9TextureLoader::D3D9TextureLoader(LPDIRECT3DDEVICE9 direct3DDevice)
		: direct3DDevice_(direct3DDevice)
	{
	}



	D3D9TextureLoader::~D3D9TextureLoader()
	{
	}



	Resource* D3D9TextureLoader::getResource(std::string textureFile)
	{
		LPDIRECT3DTEXTURE9 textureData = NULL;

		HRESULT result = D3DXCreateTextureFromFile(direct3DDevice_,
			textureFile.c_str(),
			&textureData);
		if (FAILED(result))
		{
			std::string prefixedTextureFile = "..\\" + textureFile;

			if (FAILED(D3DXCreateTextureFromFile(direct3DDevice_,
				prefixedTextureFile.c_str(),
				&textureData)))
			{
				LoggerPool::getInstance()->getLogger("TextureLoader")
					->logError("Failed to create texture from file, " + result);
			}
		}

		return new D3D9Texture(textureData);
	}
}
