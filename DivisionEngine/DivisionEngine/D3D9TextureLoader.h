#ifndef DIVISION_TEXTURELOADER_H
#define DIVISION_TEXTURELOADER_H

#include <d3d9.h>
#include <string>

#include "ResourceLoader.h"

namespace Division
{
	/**
		DirectX9 implementatiion of the resource loader interface. Creates
		d3d9 texture objects as resources. Should be created by the d3d9
		repository.
	*/
	class D3D9TextureLoader : public ResourceLoader
	{
	public:
		/**
			@param direct3DDevice The d3d9 device necessary to create d3d9
			texture data from a file.
		*/
		D3D9TextureLoader(LPDIRECT3DDEVICE9 direct3DDevice);
		~D3D9TextureLoader();
		Resource* getResource(std::string resourceName);
	private:
		LPDIRECT3DDEVICE9 direct3DDevice_ = NULL;
	};
}

#endif // !DIVISION_TEXTURELOADER_H