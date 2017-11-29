#include "Scene.h"

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

Scene::Scene()
{
}

Scene::~Scene()
{
}