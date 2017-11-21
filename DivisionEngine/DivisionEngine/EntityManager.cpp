#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::createEntity(std::string str )
{
	Entities.push_back(new Entity(str));
}
Entity * EntityManager::getEntity(std::string str)
{
	std::list<Entity*>::iterator it = std::find(Entities.begin(), Entities.end(), str);
	return *it;
}

void EntityManager::destroyEntity(std::string str)
{
	std::list<Entity*>::iterator it = std::find(Entities.begin(), Entities.end(), str);
	Entities.erase(it);
}
