#ifndef DIVISION_SCENEMANAGER_H
#define DIVISION_SCENEMANAGER_H

#include "Renderer.h"
#include "Scene.h"
#include "SceneLoader.h"
#include "ResourceManager.h"
#include "Repository.h"

#include <map>
namespace Division
{
	class SceneLoader;
	class SceneManager
	{
	public:
		SceneManager(ResourceManager*, Repository*);
		~SceneManager();
		void renderScenes();
		void addRenderer(std::string, Renderer*);
		Renderer* getRenderer(std::string);
		void removeRenderer(std::string);
		Scene* createScene(std::string);
		Scene* loadScene(std::string, std::string);
		Scene* getScene(std::string);
		void removeScene(std::string);
	private:
		std::map<std::string, Renderer*> renderers_;
		std::map<std::string, Scene*> scenes_;
		ResourceManager* resourceManager_;
		Repository* repository_;
		SceneLoader* sceneLoader_;
	};
}

#endif