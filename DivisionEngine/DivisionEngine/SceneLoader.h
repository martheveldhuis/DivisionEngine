#ifndef DIVISION_SCENELOADER_H
#define DIVISION_SCENELOADER_H

#include <string>

#include "Repository.h"
#include "ResourceManager.h"
#include "Win32Window.h"
#include "Model.h"
#include "Camera.h"

namespace Division
{
	class SceneManager;
	class SceneLoader
	{
	public:
		SceneLoader(SceneManager*, Repository*, ResourceManager*);
		~SceneLoader();
		void loadScene(std::string scene);
	private:
		Repository* d3D9Repository_;
		ResourceManager* resourceManager_;
		SceneManager* sceneManager_;
	};
}
#endif // ! DIVISION_SCENELOADER_H