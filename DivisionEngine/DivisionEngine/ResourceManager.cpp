#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

void ResourceManager::createResource(std::string str)
{
	resources.push_back(new Resource(str));
}

Resource * ResourceManager::getResource(std::string str)
{
	std::list<Resource*>::iterator it = std::find(resources.begin(), resources.end(), str);
	return *it;
}

void ResourceManager::destroyResource(std::string str)
{
	std::list<Resource*>::iterator it = std::find(resources.begin(), resources.end(), str);
	resources.erase(it);
}