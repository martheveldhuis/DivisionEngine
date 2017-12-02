#include "Entity.h"
namespace Division
{
	Entity::Entity()
	{}

	Entity::Entity(ResourceManager * rm) : resourceManager_(rm)
	{
	}

	Entity::~Entity()
	{}

	void Entity::render()
	{
		//loop through map and render mesh + text
	}

	void Entity::addResource(std::string str, Resource* res)
	{
		resources_[str] = res;
	}

	void Entity::getResource(std::string str, Resource* res)
	{
		std::map<std::string, Resource*>::iterator it;
		it = resources_.find(str);
		res = it->second;
	}

	void Entity::removeResource(std::string str)
	{
		std::map<std::string, Resource*>::iterator it;
		it = resources_.find(str);
		resources_.erase(it);
	}
}