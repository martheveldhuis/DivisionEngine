#include "D3D9Mesh.h"

namespace Division
{
	D3D9Mesh::D3D9Mesh(LPD3DXMESH meshData, D3DMATERIAL9* meshMaterials,
			   DWORD numberOfMaterials, std::vector<std::string> textureFileNames)
		: meshData_(meshData), meshMaterials_(meshMaterials), 
		  numberOfMaterials_(numberOfMaterials), textureFileNames_(textureFileNames)
	{
	}



	D3D9Mesh::~D3D9Mesh()
	{
		if (meshMaterials_ != NULL)
			delete[] meshMaterials_;

		if (meshData_ != NULL)
			meshData_->Release();
	}



	LPD3DXMESH D3D9Mesh::getMeshData()
	{
		return meshData_;
	}



	D3DMATERIAL9* D3D9Mesh::getMeshMaterials()
	{
		return meshMaterials_;
	}



	DWORD D3D9Mesh::getNumberOfMaterials()
	{
		return numberOfMaterials_;
	}



	std::vector<std::string> D3D9Mesh::getTextureFileNames()
	{
		return textureFileNames_;
	}



	void D3D9Mesh::setTextures(std::map<std::string, Resource*> textures)
	{
		textures_ = textures;
	}
}