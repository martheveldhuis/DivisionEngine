#include "ResourceManager.h"
#include "D3D9TextureLoader.h"
#include "D3D9MeshLoader.h"
#include "Mesh.h"

namespace Division 
{
	ResourceManager::ResourceManager(LPDIRECT3DDEVICE9 direct3Ddevice) 
		: direct3Ddevice_(direct3Ddevice)
	{
	}



	ResourceManager::~ResourceManager()
	{
		std::map<std::string, Resource*>::const_iterator toBeDeleted;

		toBeDeleted = textures_.begin();
		while (toBeDeleted != textures_.end()) {
			delete toBeDeleted->second;
		}
		textures_.clear();

		toBeDeleted = meshes_.begin();
		while (toBeDeleted != meshes_.end()) {
			delete toBeDeleted->second;
		}
		meshes_.clear();
	}




	Resource* ResourceManager::addNewTexture(std::string textureFile)
	{
		Resource* texture = TextureLoader::getResource(textureFile, direct3Ddevice_);
		textures_[textureFile] = texture;
		return texture;
	}



	Mesh* ResourceManager::addNewMesh(std::string meshFile)
	{
		Mesh* mesh = MeshLoader::getResource(meshFile, direct3Ddevice_);
		meshes_[meshFile] = mesh;
		return mesh;
	}



	Resource* ResourceManager::getTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);

		if (it != textures_.end())
			return it->second;
		else {
			return addNewTexture(textureFile);
		}
		
		return nullptr;
	}



	Mesh* ResourceManager::getMesh(std::string meshFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = meshes_.find(meshFile);

		Mesh* mesh;
		std::map<std::string, Resource*> textures;

		if (it != meshes_.end()) {
			 mesh = dynamic_cast<Mesh*>(it->second);
		}
		else {
			mesh = addNewMesh(meshFile);
		}

		std::vector<std::string> textureFileNames = mesh->getTextureFileNames();

		std::vector<std::string>::const_iterator textureIterator = textureFileNames.begin();
		if (textureIterator == textureFileNames.end()) {
			for (int i = 0; i < mesh->getNumberOfMaterials(); ++i) {

			}
		}
		else {
			while (textureIterator != textureFileNames.end()) {
				textures[*textureIterator] = getTexture(*textureIterator);
				++textureIterator;
			}
		}
		
		
		


		mesh->setTextures(textures);
		
		return mesh;
	}



	void ResourceManager::removeTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);
		Resource* resource = it->second;
		textures_.erase(it);
		delete resource;
	}



	void ResourceManager::removeMesh(std::string meshFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = meshes_.find(meshFile);
		Resource* resource = it->second;
		meshes_.erase(it);
		delete it->second;
	}
}