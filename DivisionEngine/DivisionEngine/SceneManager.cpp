#include "SceneManager.h"
namespace Division
{
	SceneManager::SceneManager()
	{
	}

	SceneManager::SceneManager(ResourceManager* rm) : resourceManager_(rm)
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
		rend = renderers_.find(str)->second;
	}

	void SceneManager::removeRenderer(std::string str)
	{
		renderers_.erase(renderers_.find(str));
	}

	Scene* SceneManager::createScene(std::string str, Renderer* renderer)
	{
		Scene* createdScene = new Scene(resourceManager_, renderer);
		scenes_[str] = createdScene;
		return createdScene;
	}

	void SceneManager::getScene(std::string str, Scene* scene)
	{
		scene = scenes_.find(str)->second;
	}

	void SceneManager::removeScene(std::string str)
	{
		scenes_.erase(scenes_.find(str));
	}
}