#ifndef DIVISION_MESH_H
#define DIVISION_MESH_H

#include <d3dx9.h>
#include <string>

#include "Resource.h"
#include "Texture.h"

namespace Division 
{
	class Mesh : public Resource
	{
	public:
		Mesh(LPD3DXMESH);
		~Mesh();
		void* getResourceData();
	private:
		LPD3DXMESH meshData_ = NULL;
	};
}
#endif