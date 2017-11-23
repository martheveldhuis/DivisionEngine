#include "Entity.h"

Entity::Entity()
{}

Entity::Entity(ResourceManager * rm) : resourcemanager(rm)
{
}

Entity::~Entity()
{}

void Entity::addResource(std::string str)
{
	resources.push_back(std::pair <std::string, Resource*>(str, new Resource()));
}

Resource* Entity::getResource(std::string str)
{
	std::list<std::pair<std::string, Resource*>>::iterator it = std::find_if(resources.begin(), resources.end(), [str](std::pair<std::string, Resource*> const &b) {
		return b.first == str;
	});
	return it->second;
}

void Entity::removeResource(std::string str)
{
	std::list<std::pair<std::string, Resource*>>::iterator it = std::find_if(resources.begin(), resources.end(), [str](std::pair<std::string, Resource*> const &b) {
		return b.first == str;
	});
	resources.erase(it);
}