#include "Entity.h"

Entity::Entity()
{}

Entity::Entity(ResourceManager * rm) : resourceManager_(rm)
{
}

Entity::~Entity()
{}

void Entity::addResource(std::string str)
{
	resources_.push_back(std::pair <std::string, Resource*>(str, new Resource()));
}

Resource* Entity::getResource(std::string str)
{
	std::list<std::pair<std::string, Resource*>>::iterator it = std::find_if(resources_.begin(), resources_.end(), [str](std::pair<std::string, Resource*> const &b) {
		return b.first == str;
	});
	return it->second;
}

void Entity::removeResource(std::string str)
{
	std::list<std::pair<std::string, Resource*>>::iterator it = std::find_if(resources_.begin(), resources_.end(), [str](std::pair<std::string, Resource*> const &b) {
		return b.first == str;
	});
	resources_.erase(it);
}