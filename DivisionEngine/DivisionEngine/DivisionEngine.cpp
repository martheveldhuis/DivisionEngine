#include "DivisionEngine.h"

DivisionEngine::DivisionEngine()
{
	resourceManager_ = new ResourceManager();
}

DivisionEngine::~DivisionEngine()
{
}

ResourceManager * DivisionEngine::getResourceManager()
{
	return resourceManager_;
}