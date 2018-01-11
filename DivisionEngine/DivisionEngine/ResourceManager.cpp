#include "ResourceManager.h"
#include "LoggerPool.h"

namespace Division
{
	ResourceManager::ResourceManager(ResourceLoader* textureLoader,
									 ResourceLoader* meshLoader) : 
		textureLoader_(textureLoader), meshLoader_(meshLoader)
	{
		LoggerPool::getInstance()->getLogger("resourceManager")
			->logInfo("Created ResourceManager");
	}



	ResourceManager::~ResourceManager()
	{
		std::map<std::string, Resource*>::const_iterator toBeDeleteTexture;

		toBeDeleteTexture = textures_.begin();
		while (toBeDeleteTexture != textures_.end()) {
			delete toBeDeleteTexture->second;
			++toBeDeleteTexture;
		}
		textures_.clear();

		std::map<std::string, Resource*>::const_iterator toDeleteMesh;
		toDeleteMesh = meshes_.begin();
		while (toDeleteMesh != meshes_.end()) {
			delete toDeleteMesh->second;
			++toDeleteMesh;
		}
		meshes_.clear();

		LoggerPool::getInstance()->getLogger("resourceManager")
			->logInfo("Destroyed ResourceManager");
	}



	Resource* ResourceManager::addNewTexture(std::string textureFile)
	{
		Resource* texture = textureLoader_->getResource(textureFile);
		textures_[textureFile] = texture;
		return texture;
	}



	Resource* ResourceManager::addNewMesh(std::string meshFile)
	{
		Resource* mesh = meshLoader_->getResource(meshFile);
		meshes_[meshFile] = mesh;
		return mesh;
	}



	Resource* ResourceManager::getTexture(std::string textureFile)
	{

		LoggerPool::getInstance()->getLogger("MeshLoader")->
			logInfo("Failed to load mesh from file");
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);

		Resource* texture;

		if (it != textures_.end())
			texture = it->second;
		else {
			texture = addNewTexture(textureFile);
		}

		return texture;
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
			mesh = dynamic_cast<Mesh*>(addNewMesh(meshFile));
		}

		std::vector<std::string> textureFileNames = mesh->getTextureFileNames();

		std::vector<std::string>::const_iterator textureFilesIterator;
		std::vector<std::string>::const_iterator textureFilesEnd;

		textureFilesIterator = textureFileNames.begin();
		textureFilesEnd = textureFileNames.end();

		// Add the texture to the textures map without using the texture loader.
		while (textureFilesIterator != textureFilesEnd) {
			textures[*textureFilesIterator] = getTexture(*textureFilesIterator);
			++textureFilesIterator;
		}

		mesh->setTextures(textures);

		return mesh;
	}



	void ResourceManager::removeTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);

		if (it != textures_.end()) {
			Resource* resource = it->second;
			textures_.erase(it);
			delete resource;
		}
	}



	void ResourceManager::removeMesh(std::string meshFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = meshes_.find(meshFile);

		if (it != meshes_.end()) {
			Resource* resource = it->second;
			meshes_.erase(it);
			delete resource;
		}
	}



	int ResourceManager::getNumberOfTextures()
	{
		return textures_.size();
	}



	int ResourceManager::getNumberOfMeshes()
	{
		return meshes_.size();
	}

}