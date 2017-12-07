#include "SceneManager.h"
namespace Division
{
	SceneManager::SceneManager(ResourceManager* rm) : resourceManager_(rm)
	{
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::renderScenes()
	{
		std::map<std::string, Scene*>::iterator it;
		for (it = scenes_.begin(); it != scenes_.end(); it++)
			it->second->render();
	}

	void SceneManager::addRenderer(std::string str, Renderer* rend)
	{
		renderers_[str] = rend;
	}

	Renderer* SceneManager::getRenderer(std::string str)
	{
		std::map<std::string, Renderer*>::iterator it;
		it = renderers_.find(str);
		if (it != renderers_.end())
			return it->second;
		else
			return nullptr;
	}

	void SceneManager::removeRenderer(std::string str)
	{
		std::map<std::string, Renderer*>::iterator it;
		it = renderers_.find(str);
		if (it != renderers_.end()) {
			it->second->cleanup();
			renderers_.erase(it);
		}
	}

	Scene* SceneManager::createScene(std::string str)
	{
		Scene* createdScene = new Scene(resourceManager_);
		scenes_[str] = createdScene;
		return createdScene;
	}

	void SceneManager::addScene(std::string str, Scene* rend)
	{
		scenes_[str] = rend;
	}

	Scene* SceneManager::getScene(std::string str)
	{
		std::map<std::string, Scene*>::iterator it;
		it = scenes_.find(str);
		if (it != scenes_.end())
			return it->second;
		else
			return nullptr;
	}

	void SceneManager::removeScene(std::string str)
	{
		std::map<std::string, Scene*>::iterator it;
		it = scenes_.find(str);
		if (it != scenes_.end()) {
			delete it->second;
			scenes_.erase(it);
		}
	}
}