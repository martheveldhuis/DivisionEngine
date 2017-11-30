#include "TextureLoader.h"
#include "Win32Window.h"
#include "D3D9Renderer.h"

namespace Division
{
	TextureLoader::TextureLoader()
	{
	}


	TextureLoader::~TextureLoader()
	{
	}

	LPDIRECT3DTEXTURE9 TextureLoader::getTexture(std::string textureFile)
	{
		// TODO: change this to return a texture object (resource)
		// TODO: put d3d object and d3d device somewhere so it can be shared everywhere
		Win32Window* a = new Win32Window();
		
		HWND hWnd = a->getWindowHandle();

		D3D9Renderer* rend = new D3D9Renderer(NULL,NULL, hWnd);
		rend->setup();
		LPDIRECT3DDEVICE9 g_pd3dDevice = rend->direct3Ddevice_;



		///////////////////////////////////////////////////////////////

		LPDIRECT3DTEXTURE9 texture = NULL;

		HRESULT result = D3DXCreateTextureFromFile(g_pd3dDevice, 
												   textureFile.c_str(), 
												   &texture);
		if (FAILED(result))
		{
			std::string prefixedTextureFile = "..\\" + textureFile;

			if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, 
												 prefixedTextureFile.c_str(),
												 &texture)))
			{
				// Log that this failed
			}
		}

		return texture;
	}
}
