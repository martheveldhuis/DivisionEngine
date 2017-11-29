#ifndef DIVISION_DIVISIONENGINE_H
#define DIVISION_DIVISIONENGINE_H

#include "ResourceManager.h"
#include "SceneManager.h"

class DivisionEngine
{
private:
	ResourceManager* resourceManager_;
	SceneManager* sceneManager_;

public:
	DivisionEngine();
	~DivisionEngine();

	ResourceManager* getResourceManager();
	SceneManager* getSceneManager();
};
#endif