#include "SceneManager.h"
#include "SceneLoader.h"

namespace Division
{
	SceneManager::SceneManager(ResourceManager* rm, Repository* repository_)
		: resourceManager_(rm), repository_(repository_)
	{
		inputManager_ = repository_->getInputManager();
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
			renderers_.erase(it);
		}
	}

	Scene* SceneManager::createScene(std::string str)
	{
		Scene* createdScene = new Scene(resourceManager_, inputManager_);
		scenes_[str] = createdScene;
		return createdScene;
	}

	Scene* SceneManager::loadScene(std::string scene, std::string filename)
	{
		if (sceneLoader_ == NULL) {
			sceneLoader_ = new SceneLoader(this, repository_, resourceManager_);
		}
		return sceneLoader_->loadScene(scene, filename);
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

		// Check if renderers are not in use anymore\
		// TODO : Find better solution
		for (std::map<std::string, Renderer*>::iterator it2 = renderers_.begin(); it2 != renderers_.end(); ++it2) {
			if (it2->second->getReferenceCount() == 0) {
				delete it2->second;
				renderers_.erase(it2);
			}
		}
	}
}