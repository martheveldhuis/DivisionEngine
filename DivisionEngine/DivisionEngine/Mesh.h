#ifndef DIVISION_MESH_H
#define DIVISION_MESH_H

#include <d3d9.h>
#include <string>

#include "Resource.h"
#include "Texture.h"

namespace Division
{
	class Mesh : public Resource
	{
	public:
		Mesh(std::string meshName, std::string textureName, LPDIRECT3DDEVICE9 direct3Device_);
		~Mesh();
	private:
		Texture* texture_ = NULL; // texture
		LPDIRECT3DDEVICE9 direct3Device_ = NULL; // device
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL; // buffer
		LPDIRECT3DINDEXBUFFER9 indexBuffer_ = NULL; // Buffer to hold indices
	};
}
#endif