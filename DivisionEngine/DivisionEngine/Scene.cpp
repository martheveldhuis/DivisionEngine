#include "Scene.h"
#include "Model.h"
#include "Win32Window.h"

namespace Division
{
	Scene::Scene(ResourceManager* rm) : resourceManager_(rm)
	{
	}



	Scene::~Scene()
	{
	}



	void Scene::render()
	{
		std::map<Window*, std::string>::const_iterator windowIt;

		for (windowIt = entityListToWindow_.begin(); windowIt != entityListToWindow_.end(); windowIt++)
		{
			std::map<Window*, Renderer*>::const_iterator rendererIt = rendererToWindow_.find(windowIt->first);

			if (rendererIt != rendererToWindow_.end())
				rendererIt->second->setupMatrices();

			LPDIRECT3DDEVICE9 renderDevice = static_cast<LPDIRECT3DDEVICE9>(rendererIt->second->getDevice());
			renderDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x79, 0xda, 0x33), 1.0f, 0);

			renderDevice->BeginScene();

			std::map<Window*, std::string>::const_iterator entityListIt;
			entityListIt = entityListToWindow_.find(windowIt->first);
			
			if (entityListIt != entityListToWindow_.end()) {
				std::list<Entity*> entityList = getEntityList(entityListIt->second);
				std::list<Entity*>::const_iterator entityIt;

				for (entityIt = entityList.begin(); entityIt != entityList.end(); ++entityIt) {
					(*entityIt)->render(rendererIt->second);
				}
			}

			renderDevice->EndScene();

			HWND win = static_cast<HWND>(windowIt->first->getWindowHandle());

			renderDevice->Present(NULL, NULL, win, NULL);
		}
	}



	void Scene::addWindow(std::string windowName, Window* window, Renderer* renderer)
	{
		windows_[windowName] = window;
		rendererToWindow_[window] = renderer;

	}



	Window* Scene::getWindow(std::string str)
	{
		std::map<std::string, Window*>::iterator it;
		it = windows_.find(str);
		if (it != windows_.end())
			return (it->second);
		else
			return nullptr;
	}



	void Scene::removeWindow(std::string str)
	{
		std::map<std::string, Window*>::const_iterator window;
		window = windows_.find(str);
		if (window != windows_.end())
		{
			std::map<Window*, std::string>::const_iterator entityRelations;
			std::map<Window*, Renderer*>::const_iterator rendererRelations;

			entityRelations = entityListToWindow_.find(window->second);
			rendererRelations = rendererToWindow_.find(window->second);

			if (entityRelations != entityListToWindow_.end()) {
				// TODO: clean up entityListToWindow_
			}

			if (rendererRelations != rendererToWindow_.end()) {
				// TODO: clean up rendererToWindow_
			}

			// TODO: clean up windows_
		}
	}



	void Scene::addEntityList(std::string entityListName, std::list<Entity*> entityList, Window* window)
	{
		entityLists_[entityListName] = entityList;
		entityListToWindow_[window] = entityListName;
	}



	std::list<Entity*> Scene::getEntityList(std::string entityListName)
	{
		std::map<std::string, std::list<Entity*>>::const_iterator entityLists;
		entityLists = entityLists_.find(entityListName);

		if (entityLists != entityLists_.end())
			return entityLists->second;

		return std::list<Entity*>();
	}



	void Scene::removeEntityList(std::string entityListName)
	{
		std::map<std::string, std::list<Entity*>>::const_iterator entityList;
		entityList = entityLists_.find(entityListName);
		if (entityList != entityLists_.end()) {

			std::map<Window*, std::string>::const_iterator windowsToEntityListIt;
			windowsToEntityListIt = entityListToWindow_.begin();

			while (windowsToEntityListIt != entityListToWindow_.end()) {
				if (windowsToEntityListIt->second == entityListName) {
					// TODO: cleanup entityListToWindow_
				}
			}

			// TODO: cleanup entityLists_
		}

	}
}