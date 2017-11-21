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
	inline friend bool operator==(Resource l, std::string r) {
		return getName() == r;
	}
	std::string getName();
};

#endif