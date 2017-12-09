#ifndef DIVISION_MESHLOADER_H
#define DIVISION_MESHLOADER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>

#include "D3D9Mesh.h"
#include "ResourceLoader.h"
#include "LoggerPool.h"

namespace Division
{
	class D3D9MeshLoader : public ResourceLoader
	{
	public:
		D3D9MeshLoader(LPDIRECT3DDEVICE9);
		~D3D9MeshLoader();
		Mesh* getResource(std::string);
	private:
		LPDIRECT3DDEVICE9 direct3DDevice_ = NULL;
	};
}

#endif // !DIVISION_MESHLOADER_H