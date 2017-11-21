#include "Resource.h"

Resource::Resource()
{}
Resource::Resource(std::string str) : name(str)
{}


std::string Resource::getName()
{
	return name;
}

Resource::~Resource()
{
}
