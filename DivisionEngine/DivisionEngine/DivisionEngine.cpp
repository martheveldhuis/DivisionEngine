#include "DivisionEngine.h"

namespace Division
{
	DivisionEngine::DivisionEngine()
	{
		resourceManager_ = new ResourceManager();
		sceneManager_ = new SceneManager(resourceManager_);
	}

	DivisionEngine::~DivisionEngine()
	{
		delete resourceManager_;
		delete sceneManager_;
	}

	void DivisionEngine::run()
	{
		sceneManager_->renderScenes();
	}
	SceneManager * DivisionEngine::getSceneManager()
	{
		return sceneManager_;
	}
	ResourceManager * DivisionEngine::getResourceManager()
	{
		return resourceManager_;
	}
}