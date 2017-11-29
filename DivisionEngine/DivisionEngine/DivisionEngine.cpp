#include "DivisionEngine.h"

DivisionEngine::DivisionEngine()
{
	resourceManager_ = new ResourceManager();
	sceneManager_ = new SceneManager();
}

DivisionEngine::~DivisionEngine()
{
}

ResourceManager * DivisionEngine::getResourceManager()
{
	return resourceManager_;
}

SceneManager * DivisionEngine::getSceneManager()
{
	return sceneManager_;
}