#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

void ResourceManager::addResource(Resource)
{
}

void ResourceManager::createResource(std::string str)
{
	resources[str] = new Resource();
}

Resource * ResourceManager::getResource(std::string str)
{
	std::map<std::string, Resource*>::iterator it;
	it = resources.find(str);
	return it->second;
}

void ResourceManager::destroyResource(std::string str)
{
	std::map<std::string, Resource*>::iterator it;
	it = resources.find(str);
	resources.erase(it);
}