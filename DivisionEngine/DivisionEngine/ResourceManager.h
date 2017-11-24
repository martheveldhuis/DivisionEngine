#ifndef DIVISION_RESOURCEMANAGER_H
#define DIVISION_RESOURCEMANAGER_H

#include "Resource.h"
#include <map>

class ResourceManager
{
private:
	std::map<std::string, Resource*> resources_;

public:
	ResourceManager();
	void addResource(Resource);
	void createResource(std::string);
	Resource* getResource(std::string);
	void destroyResource(std::string);
};
#endif
