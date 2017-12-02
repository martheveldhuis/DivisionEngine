#include "Mesh.h"

namespace Division
{
	Mesh::Mesh(LPD3DXMESH meshData) : meshData_(meshData)
	{
	}

	Mesh::~Mesh()
	{
	}

	void * Mesh::getResourceData()
	{
		return (void*)meshData_;
	}

}