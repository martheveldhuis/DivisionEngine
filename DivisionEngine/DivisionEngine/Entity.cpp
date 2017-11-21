#include "Entity.h"

Entity::Entity()
{}

Entity::Entity(std::string str) : name(str)
{}


Entity::~Entity()
{
}

std::string Entity::getName()
{
	return name;
}


