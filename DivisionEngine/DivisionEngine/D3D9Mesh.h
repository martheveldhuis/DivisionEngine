#ifndef DIVISION_D3D9MESH_H
#define DIVISION_D3D9MESH_H

#include <d3dx9.h>
#include <string>
#include <vector>
#include <map>

#include "Resource.h"
#include "D3D9Texture.h"
#include "DivisionMesh.h"

namespace Division 
{
	class D3D9Mesh : public DivisionMesh
	{
	public:
		D3D9Mesh(LPD3DXMESH, D3DMATERIAL9*, DWORD, std::vector<std::string>);
		~D3D9Mesh();
		LPD3DXMESH getMeshData();
		D3DMATERIAL9* getMeshMaterials();
		DWORD getNumberOfMaterials();
		std::vector<std::string> getTextureFileNames();
		void setTextures(std::map<std::string, Resource*>);
		std::map<std::string, Resource*> getTextures();
	private:
		LPD3DXMESH meshData_ = NULL; 
		D3DMATERIAL9* meshMaterials_ = NULL;
		DWORD numberOfMaterials_ = 0L;
		std::vector<std::string> textureFileNames_; // For loading textures from .x file
		std::map<std::string, Resource*> textures_;
	};
}

#endif