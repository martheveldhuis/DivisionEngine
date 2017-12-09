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


	int D3D9Mesh::getNumberOfMaterials()
	{
		return static_cast<int>(numberOfMaterials_);
	}



	std::vector<std::string> D3D9Mesh::getTextureFileNames()
	{
		return textureFileNames_;
	}



	void D3D9Mesh::setTextures(std::map<std::string, Resource*> textures)
	{
		std::map<std::string, Resource*>::const_iterator textureIterator = textures.begin();
		while (textureIterator != textures.end()) {
			textures_[textureIterator->first] = textureIterator->second;
			++textureIterator;
		}
	}



	std::map<std::string, Resource*> D3D9Mesh::getTextures()
	{
		return textures_;
	}



	void D3D9Mesh::draw(Renderer *renderer)
	{
		LPDIRECT3DDEVICE9 renderDevice = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());

		std::map<std::string, Resource*>::const_iterator textureIterator = textures_.begin();
		for (DWORD i = 0; i < numberOfMaterials_; i++) {
			renderDevice->SetMaterial(&meshMaterials_[i]);

			if (textureIterator != textures_.end()) {
				renderer->setTexture(textureIterator->second);
				++textureIterator;
			}

			meshData_->DrawSubset(i);
		}
	}
}