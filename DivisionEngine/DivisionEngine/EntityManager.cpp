#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::createEntity(std::string str)
{
	entities.push_back(new Entity(str));
}

Entity * EntityManager::getEntity(std::string str)
{
	std::list<Entity*>::iterator it = std::find(entities.begin(), entities.end(), str);
	return *it;
}

void EntityManager::destroyEntity(std::string str)
{
	std::list<Entity*>::iterator it = std::find(entities.begin(), entities.end(), str);
	entities.erase(it);
}