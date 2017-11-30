#ifndef DIVISION_MESHLOADER_H
#define DIVISION_MESHLOADER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

namespace Division
{
	class MeshLoader
	{
	public:
		MeshLoader();
		~MeshLoader();
		LPD3DXMESH getMesh(std::string);
	};
}

#endif // !DIVISION_MESHLOADER_H