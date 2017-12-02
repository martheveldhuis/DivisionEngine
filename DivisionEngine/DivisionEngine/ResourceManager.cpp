#include "ResourceManager.h"
#include "TextureLoader.h"
#include "MeshLoader.h"

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



	void ResourceManager::addNewTexture(std::string textureFile)
	{
		Resource* texture = TextureLoader::getResource(textureFile, direct3Ddevice_);
		textures_[textureFile] = texture;
	}



	void ResourceManager::addNewMesh(std::string meshFile)
	{
		Resource* mesh = MeshLoader::getResource(meshFile, direct3Ddevice_);
		meshes_[meshFile] = mesh;
	}



	Resource* ResourceManager::getTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);

		if (it != textures_.end())
			return it->second;
		else {
			addNewTexture(textureFile);
			it = textures_.find(textureFile);

			if (it != textures_.end())
				return it->second;
		}
		
		return NULL;
	}



	Resource * ResourceManager::getMesh(std::string meshFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = meshes_.find(meshFile);

		if (it != meshes_.end())
			return it->second;
		else {
			addNewMesh(meshFile);

			it = meshes_.find(meshFile);

			if (it != meshes_.end())
				return it->second;
		}
		
		return NULL;
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