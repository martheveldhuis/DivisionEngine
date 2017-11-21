#ifndef ENTITY
#define ENTITY
#include "Resource.h"
#include<string>
#include<list>

class Entity
{
private:
	std::string name;
	std::list<Resource*> Resources;
public:
	Entity();
	Entity(std::string);
	~Entity();
	friend bool operator==(Entity* l, std::string r) {
		return l->getName() == r;
	}
	friend bool operator==(std::string r, Entity* l) {
		return l->getName() == r;
	}
	std::string getName();
};

#endif