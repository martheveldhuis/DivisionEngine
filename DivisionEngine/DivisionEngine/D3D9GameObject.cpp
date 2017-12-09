#include "D3D9GameObject.h"

namespace Division
{
	D3D9GameObject::D3D9GameObject(ResourceManager* rm, float x, float y, float z) : Entity(rm, x, y, z)
	{
	}


	D3D9GameObject::~D3D9GameObject()
	{
	}



	void D3D9GameObject::render(Renderer* renderer)
	{
		D3D9Renderer* d3d9Renderer = dynamic_cast<D3D9Renderer*>(renderer);
		
		LPDIRECT3DDEVICE9 device = static_cast<LPDIRECT3DDEVICE9>(d3d9Renderer->getDevice());
		
		std::map<std::string, Resource*>::const_iterator meshIterator = meshes_.begin();
		while (meshIterator != meshes_.end()) {

			D3D9Mesh* mesh = dynamic_cast<D3D9Mesh*>(meshIterator->second);
			D3DMATERIAL9* meshMaterials = mesh->getMeshMaterials();
			std::vector<std::string> textureFileNames = mesh->getTextureFileNames();

			textures_ = mesh->getTextures();
			std::map<std::string, Resource*>::const_iterator textureIterator = textures_.begin();

			for (DWORD i = 0; i < mesh->getNumberOfMaterials(); i++)
			{

				// Set the material and texture for this subset
				device->SetMaterial(&meshMaterials[i]);

				if (textures_.size() > 0) {

					D3D9Texture* texture = dynamic_cast<D3D9Texture*>(textureIterator->second);

					if (textureIterator != textures_.end())
						d3d9Renderer->setTexture(texture);
				}
				else {
					//mesh->getTextures();
					//device->SetTexture(0, textureFileNames[i]);
				}

				// Draw the mesh subset
				LPD3DXMESH meshData = mesh->getMeshData();
				meshData->DrawSubset(i);
				if (textureIterator != textures_.end())
					++textureIterator;
			}

			++meshIterator;
		}

		


		// TODO: loop through all meshes and textures
		


			/*
			Mesh* mesh = dynamic_cast<Mesh*>(meshes_["tiger.x"]);
			std::vector<std::string> textureFileNames = mesh->getTextureFileNames();

			std::vector<std::string>::const_iterator it = textureFileNames.begin();
			while (it != textureFileNames.end()) {
			//std::string textureFileName = (*it);
			//addTexture(textureFileName, resourceManager_->getTexture(textureFileName));
			++it;
			}
			renderer->setMesh(mesh);
			*/

			/*Texture* texture = dynamic_cast<Texture*>(textures_["banana.bmp"]);
			renderer->setTexture(texture);*/
	}
}
