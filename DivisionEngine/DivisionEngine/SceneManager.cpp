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

	void SceneManager::addRenderer(std::string str, Renderer* rend)
	{
		renderers_[str] = rend;
	}

	void SceneManager::getRenderer(std::string str, Renderer* rend)
	{
		if (renderers_.find(str) != renderers_.end()) {
			rend = renderers_.find(str)->second;
		}
	}

	void SceneManager::removeRenderer(std::string str)
	{
		// TODO: implement properly
		//renderers_.erase(renderers_.find(str));
	}

	Scene* SceneManager::createScene(std::string str, Renderer* renderer)
	{
		Scene* createdScene = new Scene(resourceManager_, renderer);
		scenes_[str] = createdScene;
		return createdScene;
	}

	Scene* SceneManager::loadScene(std::string sceneFile)
	{
		Division::Win32Window* win = new Division::Win32Window("Window", "Window title");
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
		// TODO: implement properly
		//scenes_.erase(scenes_.find(str));
	}
}