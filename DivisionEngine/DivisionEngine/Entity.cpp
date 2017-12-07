#include "Entity.h"

namespace Division
{
	Entity::Entity(ResourceManager *resourceManager, float x = 0, float y = 0, float z = 0)
		: resourceManager_(resourceManager)
	{
		position_.xPosition = x;
		position_.yPosition = y;
		position_.zPosition = z;
	}

	Entity::~Entity()
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

	void Entity::addTexture(std::string textureFile)
	{
		textures_[textureFile] = resourceManager_->getTexture(textureFile);
	}

	void Entity::addMesh(std::string meshFile)
	{
		meshes_[meshFile] = resourceManager_->getMesh(meshFile);
	}

	Resource* Entity::getTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);
		return it->second;
	}

	Resource* Entity::getMesh(std::string meshFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(meshFile);
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
		std::map<std::string, Resource*>::iterator it;
		it = meshes_.find(meshFile);
		Resource* resource = it->second;
		meshes_.erase(it);
		delete resource;
	}
}