#ifndef DIVISION_SCENE_H
#define DIVISION_SCENE_H

#include <map>

#include "Entity.h"
#include "Renderer.h"
#include "Window.h"
#include "ResourceManager.h"

namespace Division
{
	struct DivisionWindow
	{
		Window* window;
		Renderer* renderer;
		DivisionWindow(Window* w, Renderer* r) : window(w), renderer(r)
		{}
		DivisionWindow() : window(nullptr), renderer(nullptr)
		{}
	};
	struct DivisionEntity
	{
		Entity* entity;
		Window* window;
		DivisionEntity(Entity* e, Window* w) : entity(e), window(w)
		{}
		DivisionEntity() : entity(nullptr), window(nullptr)
		{}
	};

	class Scene
	{
	public:
		Scene(ResourceManager*);
		~Scene();

		void render();

		void addWindow(std::string, DivisionWindow);
		DivisionWindow* getWindow(std::string);
		void removeWindow(std::string);

		void addEntity(std::string, DivisionEntity);
		/*std::pair<Entity*, Window*>* createEntity(std::string, Window*);*/ //TODO since entity is pure virtual cant make one.
		DivisionEntity* getEntity(std::string);
		void removeEntity(std::string);

	private:
		std::map<std::string, DivisionWindow> windows_;
		std::map<std::string, DivisionEntity> entities_;
		ResourceManager* resourceManager_;
	};
}

#endif
