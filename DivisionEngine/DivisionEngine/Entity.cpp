#include "Entity.h"

Entity::Entity()
{}

Entity::Entity(std::string str) : name(str)
{}

Entity::~Entity()
{}

std::string Entity::getName()
{
	return name;
}

void Entity::addResource(std::string str)
{
	resources.push_back(new Resource(str));
}

Resource* Entity::getResource(std::string str)
{
	std::list<Resource*>::iterator it = std::find(resources.begin(), resources.end(), str);
	return *it;
}

void Entity::removeResource(std::string str)
{
	std::list<Resource*>::iterator it = std::find(resources.begin(), resources.end(), str);
	resources.erase(it);
}