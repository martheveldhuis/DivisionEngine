#include "SceneManager.h"

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

void SceneManager::addScene(std::string str, Scene* scene)
{
	scenes_[str] = scene;
}

void SceneManager::createScene(std::string str)
{
	scenes_[str] = new Scene();
}

void SceneManager::getScene(std::string str, Scene* scene)
{
	scene = scenes_.find(str)->second;
}

void SceneManager::removeScene(std::string str)
{
	scenes_.erase(scenes_.find(str));
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}