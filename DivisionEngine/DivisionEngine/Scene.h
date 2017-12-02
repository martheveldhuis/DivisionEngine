#ifndef DIVISION_SCENE_H
#define DIVISION_SCENE_H

#include <map>

#include "Entity.h"
#include "D3D9Renderer.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Terrain.h"

namespace Division {
	class Scene
	{
	public:
		Scene();
		Scene(ResourceManager*, Renderer* renderer);
		~Scene();

		void addWindow(std::string, Window*);
		void getWindow(std::string, Window*);
		void removeWindow(std::string);
		void addRenderer(std::string, Renderer*);
		void getRenderer(std::string, Renderer*);
		void removeRenderer(std::string);
		void begin();
	private:
		std::map<std::string, Window*> windows_;
		std::map<std::string, Renderer*> renderers_;
		std::map<std::string, Entity*> entities_;
		Terrain* terrain_;
		ResourceManager* resourceManager_;
		Renderer* renderer_;
	};
}

#endif
