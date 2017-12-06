#include "Scene.h"
#include "Model.h"
namespace Division
{
	Scene::Scene()
	{
	}

	Scene::Scene(ResourceManager * rm, Renderer* renderer) : resourceManager_(rm)
	{
		addRenderer("main", renderer);
	}

	Scene::~Scene()
	{
	}

	void Scene::addWindow(std::string str, Window* window)
	{
		windows_[str] = window;
	}

	Window* Scene::getWindow(std::string name)
	{
		std::map<std::string, Window*>::const_iterator found = windows_.find(name);

		if (found != windows_.end()) {
			return found->second;
		}

		return nullptr;
	}

	void Scene::removeWindow(std::string str)
	{
		//TODO add exist check
		windows_.erase(windows_.find(str));
	}

	void Scene::addRenderer(std::string name, Renderer* renderer)
	{
		renderers_[name] = renderer;
	}

	Renderer* Scene::getRenderer(std::string name)
	{
		std::map<std::string, Renderer*>::const_iterator found = renderers_.find(name);

		if (found != renderers_.end()) {
			return found->second;
		}

		return nullptr;
	}

	void Scene::removeRenderer(std::string name)
	{
		//TODO add exist check
		renderers_.erase(renderers_.find(name));
	}

	void Scene::addEntity(std::string name, Entity* entity)
	{
		entities_[name] = entity;
	}

	Entity* Scene::getEntity(std::string name)
	{
		std::map<std::string, Entity*>::const_iterator found = entities_.find(name);

		if (found != entities_.end()) {
			return found->second;
		}

		return nullptr;
	}

	void Scene::removeEntity(std::string name)
	{
		//TODO add exist check  ...
		//renderers_.erase(renderers_.find(name));
	}
	void Scene::begin()
	{

		renderer_ = this->getRenderer("main");
		renderer_->setupMatrices();

		LPDIRECT3DDEVICE9 renderDevice = static_cast<LPDIRECT3DDEVICE9>(renderer_->getDevice());
		renderDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0xff, 0xff), 1.0f, 0);

		renderDevice->BeginScene();

		//loop through entities
		std::map<std::string, Entity*>::const_iterator entityIterator = entities_.begin();
		while (entityIterator != entities_.end()) {
			//D3D9GameObject* go = dynamic_cast<D3D9GameObject*>(entityIterator->second);
			entityIterator->second->render(renderer_);

			++entityIterator;
		}

		terrain_->render(renderer_);


		renderDevice->EndScene();

		 //Present the backbuffer contents to the display
		renderDevice->Present(NULL, NULL, NULL, NULL);
	}
}