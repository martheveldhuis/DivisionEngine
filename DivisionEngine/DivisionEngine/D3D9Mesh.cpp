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



	void D3D9Mesh::setTextures(std::map<std::string, Resource*> textures)
	{
		std::map<std::string, Resource*>::const_iterator textureIterator;
		std::map<std::string, Resource*>::const_iterator textureEnd;

		textureIterator = textures.begin();
		textureEnd = textures.end();

		while (textureIterator != textureEnd) {
			textures_[textureIterator->first] = textureIterator->second;
			++textureIterator;
		}
	}
	


	std::vector<std::string> D3D9Mesh::getTextureFileNames()
	{
		return textureFileNames_;
	}



	void D3D9Mesh::draw(Renderer *renderer, std::map<std::string, Resource*> customTextures)
	{
		LPDIRECT3DDEVICE9 renderDevice = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());
		std::map<std::string, Resource*>::const_iterator textureIterator;
		std::map<std::string, Resource*>::const_iterator textureEnd;

		if (customTextures.size() == 0) {
			textureIterator = textures_.begin();
			textureEnd = textures_.end();
		}
		else {
			textureIterator = customTextures.begin();
			textureEnd = customTextures.end();
		}


		for (DWORD i = 0; i < numberOfMaterials_; i++) {
			if (meshMaterials_)
				renderDevice->SetMaterial(&meshMaterials_[i]);

			if (textureIterator != textureEnd) {
				renderer->setTexture(textureIterator->second);
				++textureIterator;
			}

			meshData_->DrawSubset(i);
		}
	}
}