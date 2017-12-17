#ifndef DIVISION_SCENELOADER_H
#define DIVISION_SCENELOADER_H

#include <string>

#include "Repository.h"
#include "ResourceManager.h"
#include "Scene.h"

namespace Division
{
	class SceneManager;
	class SceneLoader
	{
	public:
		SceneLoader(SceneManager*, Repository*, ResourceManager*);
		~SceneLoader();
		Scene* loadScene(std::string scene, std::string filename);
	private:
		Repository* repository_;
		ResourceManager* resourceManager_;
		SceneManager* sceneManager_;
	};
}
#endif // ! DIVISION_SCENELOADER_H