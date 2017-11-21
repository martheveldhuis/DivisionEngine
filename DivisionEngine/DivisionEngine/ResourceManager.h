#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER
#include "Resource.h"
#include <list>

class ResourceManager
{
public:
	ResourceManager();
	void createResource(std::string);
	Resource* getResource(std::string);
	void destroyResource(std::string);
private:
	std::list<Resource*> Resources;
};
#endif //SOME_NAME_H
