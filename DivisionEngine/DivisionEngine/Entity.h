#ifndef ENTITY
#define ENTITY
#include "Resource.h"
#include "ResourceManager.h"
#include <list>
#include <algorithm>

class Entity
{
private:
	std::list<std::pair<std::string, Resource*>> resources;
	ResourceManager* resourcemanager;

public:
	Entity();
	Entity(ResourceManager*);
	~Entity();

	void addResource(std::string);
	Resource* getResource(std::string);
	void removeResource(std::string);
};

#endif