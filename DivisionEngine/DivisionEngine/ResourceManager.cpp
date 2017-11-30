#include "ResourceManager.h"

namespace Division 
{
	ResourceManager::ResourceManager()
	{
	}



	ResourceManager::~ResourceManager()
	{
	}



	void ResourceManager::addResource(std::string str, Resource* res)
	{
		resources_[str] = res;
	}



	void ResourceManager::getResource(std::string str, Resource* res)
	{
		std::map<std::string, Resource*>::iterator it;
		it = resources_.find(str);
		res = it->second;
	}



	void ResourceManager::destroyResource(std::string str)
	{
		std::map<std::string, Resource*>::iterator it;
		it = resources_.find(str);
		resources_.erase(it);
	}
}