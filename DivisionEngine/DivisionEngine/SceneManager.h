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
		SceneManager();
		SceneManager(ResourceManager*);
		~SceneManager();

		void addRenderer(std::string, Renderer*);
		void getRenderer(std::string, Renderer*);
		void removeRenderer(std::string);

		Scene* createScene(std::string, Renderer*);
		void getScene(std::string, Scene*);
		void removeScene(std::string);
	};
}

#endif