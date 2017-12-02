#include "Entity.h"
#include "Texture.h"

namespace Division 
{
	Entity::Entity(ResourceManager *resourceManager, std::string textureFile, std::string meshFile)
		: resourceManager_(resourceManager)
	{
		addTexture(textureFile, resourceManager_->getTexture(textureFile));
		addMesh(meshFile, resourceManager_->getMesh(meshFile));
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



	void Entity::render(Renderer* renderer)
	{
		// TODO: loop through all textures and meshes
		Texture* texture = dynamic_cast<Texture*>(textures_["banana.bmp"]);
		renderer->setTexture((void*)texture->getResourceData());
	}



	void Entity::addTexture(std::string textureFile, Resource *texture)
	{
		textures_[textureFile] = texture;
	}



	void Entity::addMesh(std::string meshFile, Resource *mesh)
	{
		meshes_[meshFile] = mesh;
	}



	Resource* Entity::getTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);
		return it->second;
	}



	Resource * Entity::getMesh(std::string meshFile)
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