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

namespace Division
{
	class Scene
	{
	public:
		Scene(ResourceManager*);
		~Scene();
		void render();
		void addWindow(std::string, Window*, Renderer*);
		Window* getWindow(std::string);
		void removeWindow(std::string);
		void addEntity(std::string, Entity*);
		Entity* getEntity(std::string);
		void removeEntity(std::string);
	private:
		ResourceManager* resourceManager_; 
		std::map<std::string,Entity*> entities_;
		std::map<std::string, Window*> windows_;
		std::map<Window*, Renderer*> rendererToWindow_;
	};
}

#endif
