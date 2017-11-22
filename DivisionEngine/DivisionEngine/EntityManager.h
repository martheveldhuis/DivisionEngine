#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER
#include "Entity.h"
#include <list>

class EntityManager
{
private:
	std::list<Entity*> entities;

public:
	EntityManager();

	void createEntity(std::string);
	Entity* getEntity(std::string);
	void destroyEntity(std::string);
};

#endif