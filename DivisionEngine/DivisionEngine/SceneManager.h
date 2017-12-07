#ifndef DIVISION_SCENEMANAGER_H
#define DIVISION_SCENEMANAGER_H

#include "Renderer.h"
#include "Scene.h"
#include "SceneLoader.h"
#include "ResourceManager.h"
#include "D3D9Repository.h"

#include <map>
namespace Division
{
	class SceneManager
	{
	public:
		SceneManager();
		SceneManager(ResourceManager*);
		~SceneManager();

		void addRenderer(std::string, Renderer*);
		void getRenderer(std::string, Renderer*);
		void removeRenderer(std::string);

		Scene* createScene(std::string, Renderer*);
		Scene* loadScene(std::string);
		Scene* getScene(std::string);
		void removeScene(std::string);
	private:
		std::map<std::string, Renderer*> renderers_;
		std::map<std::string, Scene*> scenes_;
		ResourceManager* resourceManager_;
	};
}

#endif