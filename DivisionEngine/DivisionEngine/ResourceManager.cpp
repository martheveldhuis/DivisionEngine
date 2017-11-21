#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}
void ResourceManager::createResource(std::string str)
{
	Resources.push_back(new Resource(str));
}
Resource * ResourceManager::getResource(std::string str)
{
	std::list<Resource*>::iterator it = std::find(Resources.begin(), Resources.end(), str);
	return *it;
}

void ResourceManager::destroyResource(std::string str)
{
	std::list<Resource*>::iterator it = std::find(Resources.begin(), Resources.end(), str);
	Resources.erase(it);
}
