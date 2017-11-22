#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER
#include "Resource.h"
#include <list>

class ResourceManager
{
private:
	std::list<Resource*> resources;

public:
	ResourceManager();

	void createResource(std::string);
	Resource* getResource(std::string);
	void destroyResource(std::string);
};
#endif
