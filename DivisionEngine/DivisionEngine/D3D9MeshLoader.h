#ifndef DIVISION_D3D9MESHLOADER_H
#define DIVISION_D3D9MESHLOADER_H

#include <d3d9.h>
#include <string>

#include "MeshLoader.h"
#include "Mesh.h"
#include "D3D9Mesh.h"

namespace Division
{
	/**
		DirectX9 implementatiion of the resource loader interface. Creates
		d3d9 mesh objects as resources. Should be created by the d3d9
		repository.
	*/
	class D3D9MeshLoader : public MeshLoader
	{
	public:
		/**
			@param direct3DDevice The d3d9 device necessary to create d3d9
			mesh data from a file.
		*/
		D3D9MeshLoader(LPDIRECT3DDEVICE9 direct3DDevice);
		~D3D9MeshLoader();
		Mesh* getResource(std::string resourceName);
		Mesh* getSkyBox();
	private:
		LPDIRECT3DDEVICE9 direct3DDevice_ = NULL;
	};
}

#endif // !DIVISION_D3D9MESHLOADER_H