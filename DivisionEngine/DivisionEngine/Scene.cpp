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
		std::map<std::string, DivisionWindow>::iterator it_windows;
		for (it_windows = windows_.begin(); it_windows != windows_.end(); it_windows++)
		{
			it_windows->second.renderer->setupMatrices();

			LPDIRECT3DDEVICE9 renderDevice = static_cast<LPDIRECT3DDEVICE9>(it_windows->second.renderer->getDevice());
			renderDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0xff, 0xff), 1.0f, 0);

			renderDevice->BeginScene();

			std::map<std::string, DivisionEntity>::iterator it_entity;
			for (it_entity = entities_.begin(); it_entity != entities_.end(); it_entity++) {
				if (it_entity->second.window == it_windows->second.window) {
					it_entity->second.entity->render(it_windows->second.renderer);
				}
			}

			renderDevice->EndScene();

			HWND win = static_cast<HWND>(it_windows->second.window->getWindowHandle());

			renderDevice->Present(NULL, NULL, win, NULL);
		}
	}

	void Scene::addWindow(std::string str, DivisionWindow win)
	{
		windows_[str] = win;
	}

	DivisionWindow* Scene::getWindow(std::string str)
	{
		std::map<std::string, DivisionWindow>::iterator it;
		it = windows_.find(str);
		if (it != windows_.end())
			return &(it->second);
		else
			return nullptr;
	}

	void Scene::removeWindow(std::string str)
	{
		std::map<std::string, DivisionWindow>::iterator it;
		it = windows_.find(str);
		if (it != windows_.end())
		{
			delete it->second.window;
			//it->second.renderer.decreaseReference(); //TODO add call too refrence count decreaser of renderer.
			windows_.erase(it);
		}
	}

	void Scene::addEntity(std::string str, DivisionEntity ent)
	{
		entities_[str] = ent;
	}

	//std::pair<Entity*, Window*>* Scene::createEntity(std::string str, Window* win)
	//{
	//	std::pair<Entity*, Window*> ent = std::pair<Entity*, Window*>(new Entity(resourceManager_, 0, 0, 0), win);
	//	entities_[str] = ent;
	//	return &ent;
	//}

	DivisionEntity* Scene::getEntity(std::string str)
	{
		std::map<std::string, DivisionEntity>::iterator it;
		it = entities_.find(str);
		if (it != entities_.end()) {
			return &(it->second);
		}
		return nullptr;
	}

	void Scene::removeEntity(std::string str)
	{
		//TODO add exist check  ...
		//renderers_.erase(renderers_.find(name));
	}
}