#include "SceneManager.h"
namespace Division
{
	SceneManager::SceneManager(ResourceManager* rm, Repository* repository_)
		: resourceManager_(rm), repository_(repository_)
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

	Scene* SceneManager::createScene(std::string str, Renderer* renderer)
	{
		Scene* createdScene = new Scene(resourceManager_);
		scenes_[str] = createdScene;
		return createdScene;
	}

	Scene* SceneManager::loadScene(std::string sceneFile)
	{
		SceneLoader* loader = new SceneLoader(this, repository_, resourceManager_);
		loader->loadScene(sceneFile);

		return getScene(sceneFile);
	}

	Scene* SceneManager::getScene(std::string str)
	{
		std::map<std::string, Scene*>::iterator it = scenes_.find(str);
		if (it != scenes_.end()) {
			return it->second;
		}
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