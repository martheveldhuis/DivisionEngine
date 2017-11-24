#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER
#include "Resource.h"
#include <map>

class ResourceManager
{
private:
	std::map<std::string, Resource*> resources;

public:
	ResourceManager();
	void addResource(Resource);
	void createResource(std::string);
	Resource* getResource(std::string);
	void destroyResource(std::string);
};
#endif
