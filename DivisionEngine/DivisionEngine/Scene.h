#ifndef DIVISION_SCENE_H
#define DIVISION_SCENE_H

#include <map>
#include <list>
#include <string>
#include <d3dx9.h>

#include "Entity.h"
#include "Renderer.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "InputManager.h"

namespace Division
{
	class Scene
	{
	public:
		Scene(ResourceManager*, InputManager*);
		~Scene();
		void render();
		void addWindow(std::string, Window*, Renderer*, Camera*);
		Window* getWindow(std::string);
		void removeWindow(std::string);
		void addEntityList(std::string, std::list<Entity*>, Window*);
		std::list<Entity*> getEntityList(std::string);
		void removeEntityList(std::string);
	private:
		ResourceManager* resourceManager_; 
		std::map<std::string, std::list<Entity*>> entityLists_;
		std::map<std::string, Window*> windows_;
		std::map<Window*, std::string> entityListToWindow_;
		std::map<Window*, Renderer*> rendererToWindow_;
		InputManager* inputManager_;
		std::map<Window*, Camera*> cameraToWindow_;
	};
}

#endif
