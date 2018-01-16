#ifndef DIVISION_SCENEMANAGER_H
#define DIVISION_SCENEMANAGER_H

#include <map>

#include "Renderer.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Repository.h"
#include "InputManager.h"

namespace Division
{
	class SceneLoader;
	class SceneManager
	{
	public:
		SceneManager(ResourceManager*, Repository*);
		~SceneManager();
		void renderScenes();
		void setInputHandle(void*);
		void* getInputHandle();
		void addRenderer(std::string, Renderer*);
		Renderer* getRenderer(std::string);
		void removeRenderer(std::string);
		Scene* createScene(std::string);
		Scene* loadScene(std::string);
		Scene* getScene(std::string);
		void removeScene(std::string);
	private:
		std::map<std::string, Renderer*> renderers_;
		std::map<std::string, Scene*> scenes_;
		ResourceManager* resourceManager_;
		InputManager* inputManager_;
		Repository* repository_;
		SceneLoader* sceneLoader_;
	};
}

#endif