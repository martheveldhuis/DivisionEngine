#ifndef DIVISION_ENTITY_H
#define DIVISION_ENTITY_H
#include "Resource.h"
#include "ResourceManager.h"
#include <list>
#include <algorithm>

class Entity
{
private:
	std::list<std::pair<std::string, Resource*>> resources_;
	ResourceManager* resourceManager_;

public:
	Entity();
	Entity(ResourceManager*);
	~Entity();

	void addResource(std::string);
	Resource* getResource(std::string);
	void removeResource(std::string);
};

#endif