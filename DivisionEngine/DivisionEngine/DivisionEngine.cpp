#include "DivisionEngine.h"
namespace Division
{
	DivisionEngine::DivisionEngine()
	{
		resourceManager_ = new ResourceManager();
		sceneManager_ = new SceneManager();
	}

	DivisionEngine::~DivisionEngine()
	{
	}

	void DivisionEngine::getResourceManager(ResourceManager* res)
	{
		res = resourceManager_;
	}

	void DivisionEngine::getSceneManager(SceneManager* scen)
	{
		scen = sceneManager_;
	}
}