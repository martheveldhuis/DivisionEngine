#include "Scene.h"
namespace Division {
	Scene::Scene()
	{
	}

	Scene::Scene(ResourceManager * rm) : resourceManager_(rm)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::addWindow(std::string str, Window* window)
	{
		windows_[str] = window;
	}

	void Scene::getWindow(std::string str, Window* window)
	{
		window = windows_.find(str)->second;
	}

	void Scene::removeWindow(std::string str)
	{
		windows_.erase(windows_.find(str));
	}
}