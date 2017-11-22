#include "Resource.h"

Resource::Resource()
{}
Resource::Resource(std::string str) : name(str)
{}
Resource::~Resource()
{}

std::string Resource::getName()
{
	return name;
}