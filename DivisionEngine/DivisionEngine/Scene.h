#ifndef DIVISION_SCENE_H
#define DIVISION_SCENE_H

#include <map>
#include <string>

#include "Entity.h"
#include "Renderer.h"
#include "Window.h"
#include "ResourceManager.h"
#include "InputManager.h"

namespace Division
{
	class Scene
	{
	public:
		Scene(ResourceManager*, InputManager*);
		~Scene();
		void render();
		void addWindow(std::string, Window*, Renderer*, Entity*);
		Window* getWindow(std::string);
		void removeWindow(std::string);
		void addEntity(std::string, Entity*);
		Entity* getEntity(std::string);
		void removeEntity(std::string);
	private:
		ResourceManager* resourceManager_;
		InputManager* inputManager_;
		std::map<std::string, Entity*> entities_;
		std::map<std::string, Window*> windows_;
		std::map<Window*, Renderer*> rendererToWindow_;
		std::map<Window*, Entity*> cameraToWindow_;
	};
}

#endif
