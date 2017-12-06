#include "Entity.h"

namespace Division 
{
	Entity::Entity(ResourceManager *resourceManager, float x, float y, float z)
		: resourceManager_(resourceManager)
	{
		position_.xPosition = x;
		position_.yPosition = y;
		position_.zPosition = z;
	}



	Entity::~Entity()
	{
		std::map<std::string, Resource*>::const_iterator textureToBeDeleted;

		textureToBeDeleted = textures_.begin();
		while (textureToBeDeleted != textures_.end()) {
			delete textureToBeDeleted->second;
		}
		textures_.clear();

		std::map<std::string, Mesh*>::const_iterator meshToBeDeleted;

		meshToBeDeleted = meshes_.begin();
		while (meshToBeDeleted != meshes_.end()) {
			delete meshToBeDeleted->second;
		}
		meshes_.clear();
	}



	Resource* Entity::addTexture(std::string textureFile)
	{
		Resource* texture = resourceManager_->getTexture(textureFile);
		textures_[textureFile] = texture;
		return texture;
	}



	Mesh* Entity::addMesh(std::string meshFile)
	{
		Mesh* mesh = resourceManager_->getMesh(meshFile);
		meshes_[meshFile] = mesh;
		return mesh;
	}



	Resource* Entity::getTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);

		if (it != textures_.end())
			return it->second;
		else {
			return addTexture(textureFile);
		}

		return it->second;
	}



	Mesh* Entity::getMesh(std::string meshFile)
	{
		std::map<std::string, Mesh*>::iterator it;
		it = meshes_.find(meshFile);
		return it->second;

		if (it != meshes_.end())
			return it->second;
		else {
			return addMesh(meshFile);
		}

		return it->second;
	}



	void Entity::removeTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);
		Resource* resource = it->second;
		textures_.erase(it);
		delete resource;
	}



	void Entity::removeMesh(std::string meshFile)
	{
		std::map<std::string, Mesh*>::iterator it;
		it = meshes_.find(meshFile);
		Mesh* resource = it->second;
		meshes_.erase(it);
		delete resource;
	}



	void Entity::render(Renderer* renderer)
	{
		std::map<std::string, Mesh*>::const_iterator meshIterator = meshes_.begin();
		while (meshIterator != meshes_.end()) {
			meshIterator->second->draw(renderer);
			++meshIterator;
		}
	}
}