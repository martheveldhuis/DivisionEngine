#ifndef DIVISION_SCENEMANAGER_H
#define DIVISION_SCENEMANAGER_H

#include "Renderer.h"
#include "Scene.h"
#include "ResourceManager.h"

#include <map>
namespace Division
{
	class SceneManager
	{
	private:
		std::map<std::string, Renderer*> renderers_;
		std::map<std::string, Scene*> scenes_;
		ResourceManager* resourceManager_;
	public:
		SceneManager(ResourceManager*);
		~SceneManager();

		void renderScenes();

		void addRenderer(std::string, Renderer*);
		Renderer* getRenderer(std::string);
		void removeRenderer(std::string);

		Scene* createScene(std::string);
		void addScene(std::string, Scene*);
		Scene* getScene(std::string);
		void removeScene(std::string);
	};
}

#endif