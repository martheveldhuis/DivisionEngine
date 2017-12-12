#include "Entity.h"
#include "LoggerPool.h"

namespace Division
{
	Entity::Entity(ResourceManager *resourceManager, 
		float x, float y, float z,
		float xAngle, float yAngle, float zAngle)
		: resourceManager_(resourceManager)
	{
		position_.xPosition = x;
		position_.yPosition = y;
		position_.zPosition = z;
		position_.xAngle = xAngle;
		position_.yAngle = yAngle;
		position_.zAngle = zAngle;

		LoggerPool::getInstance()->getLogger("Entity")
			->logInfo("Created Entity");
	}

	Entity::~Entity()
	{
		textures_.clear();
		meshes_.clear();

		LoggerPool::getInstance()->getLogger("Entity")
			->logInfo("Destroyed Entity");
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



	void Entity::setTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);

		if (it != textures_.end())
			textures_[textureFile] = it->second;
		else {
			addTexture(textureFile);
		}
	}



	void Entity::setMesh(std::string meshFile)
	{
		std::map<std::string, Mesh*>::iterator it;
		it = meshes_.find(meshFile);

		if (it != meshes_.end())
			meshes_[meshFile] = it->second;
		else {
			addMesh(meshFile);
		}
	}



	void Entity::removeTexture(std::string textureFile)
	{
		std::map<std::string, Resource*>::iterator it;
		it = textures_.find(textureFile);

		if (it != textures_.end()) {
			Resource* resource = it->second;
			textures_.erase(it);
			delete resource;
		}
	}



	void Entity::removeMesh(std::string meshFile)
	{
		std::map<std::string, Mesh*>::iterator it;
		it = meshes_.find(meshFile);

		if (it != meshes_.end()) {
			Resource* resource = it->second;
			meshes_.erase(it);
			delete resource;
		}
	}



	void Entity::render(Renderer* renderer)
	{
		std::map<std::string, Mesh*>::const_iterator meshIterator = meshes_.begin();
		while (meshIterator != meshes_.end()) {
			renderer->setWorldMatrix(&position_);
			meshIterator->second->draw(renderer,  textures_);
			++meshIterator;
		}
	}
}