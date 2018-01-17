#include "SceneManager.h"
#include "SceneLoader.h"

namespace Division
{
	SceneManager::SceneManager(ResourceManager* rescourcemanager, Repository* repository) :
		resourceManager_(rescourcemanager), repository_(repository)
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



	void SceneManager::setInputHandle(void * handle)
	{
		inputManager_->setWindowHandle(handle);
	}



	void * SceneManager::getInputHandle()
	{
		return inputManager_->getWindowHandle();
	}



	void SceneManager::addRenderer(std::string rendererName, Renderer* renderer)
	{
		renderers_[rendererName] = renderer;
	}



	Renderer* SceneManager::getRenderer(std::string rendererName)
	{
		std::map<std::string, Renderer*>::iterator it;
		it = renderers_.find(rendererName);
		if (it != renderers_.end())
			return it->second;
		else
			return nullptr;
	}



	void SceneManager::removeRenderer(std::string rendererName)
	{
		std::map<std::string, Renderer*>::iterator it;
		it = renderers_.find(rendererName);
		if (it != renderers_.end()) {
			renderers_.erase(it);
		}
	}



	Scene* SceneManager::createScene(std::string sceneName)
	{
		scenes_[sceneName] = new Scene(resourceManager_, inputManager_);
		return scenes_[sceneName];
	}



	Scene* SceneManager::loadScene(std::string sceneName, std::string sceneFileName)
	{
		// Check if sceneloader exists if not request one from the repository.
		if (sceneLoader_ == NULL) {
			sceneLoader_ = new SceneLoader(this, repository_, resourceManager_);
		}
		return sceneLoader_->loadScene(sceneName, sceneFileName);
	}



	Scene* SceneManager::getScene(std::string sceneName)
	{
		std::map<std::string, Scene*>::iterator it = scenes_.find(sceneName);
		if (it != scenes_.end()) {
			return it->second;
		}
		return nullptr;
	}



	void SceneManager::removeScene(std::string sceneName)
	{
		std::map<std::string, Scene*>::iterator it;
		it = scenes_.find(sceneName);
		if (it != scenes_.end()) {
			delete it->second;
			scenes_.erase(it);
		}

		// Check if any of the renderer's are not in use anymore
		// TODO : Find better solution
		for (std::map<std::string, Renderer*>::iterator it2 = renderers_.begin(); it2 != renderers_.end(); ++it2) {
			if (it2->second->getReferenceCount() == 0) {
				delete it2->second;
				renderers_.erase(it2);
			}
		}
	}
}