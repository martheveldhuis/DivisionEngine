#include "Scene.h"

#include "Camera.h"
#include "LoggerPool.h"

namespace Division
{
	Scene::Scene(ResourceManager* rm, InputManager* im) : resourceManager_(rm), inputManager_(im)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::render()
	{
		std::map<std::string, Window*>::const_iterator windowIt = windows_.begin();
		std::map<std::string, Window*>::const_iterator windowsEnd = windows_.end();

		for (; windowIt != windowsEnd; ++windowIt) {
			std::map<Window*, Renderer*>::const_iterator rendererIt;
			rendererIt = rendererToWindow_.find(windowIt->second);

			if (rendererIt == rendererToWindow_.end()) {
				LoggerPool::getInstance()->getLogger("scene")
					->logError("No renderers found while trying to render");
				return;
			}

			rendererIt->second->clear();
			rendererIt->second->beginScene();

			std::map<std::string, Entity*>::const_iterator enitityIt = entities_.begin();
			std::map<std::string, Entity*>::const_iterator enititiesEnd = entities_.end();

			for (; enitityIt != enititiesEnd; enitityIt++) {
				InputStates i = inputManager_->getInput();
				cameraToWindow_[windowIt->second]->updateCameraPosition(&i);
				enitityIt->second->render(rendererIt->second);
			}

			rendererIt->second->endScene();
			rendererIt->second->present(windowIt->second->getWindowHandle());
		}
	}



	void Scene::addWindow(std::string windowName, Window* window, Renderer* renderer, Camera* camera)
	{
		windows_[windowName] = window;
		rendererToWindow_[window] = renderer;
		cameraToWindow_[window] = camera; // TODO: delete this one when destroying scene

		renderer->setCamera(camera);
		inputManager_->setWindowHandle(window->getWindowHandle());

	}

	Window* Scene::getWindow(std::string windowName)
	{
		std::map<std::string, Window*>::iterator it;
		it = windows_.find(windowName);
		if (it != windows_.end())
			return (it->second);
		else
			return nullptr;
	}

	void Scene::removeWindow(std::string windowName)
	{
		std::map<std::string, Window*>::const_iterator window;
		window = windows_.find(windowName);
		if (window != windows_.end())
		{
			std::map<Window*, Renderer*>::const_iterator rendererRelations;
			rendererRelations = rendererToWindow_.find(window->second);
			if (rendererRelations != rendererToWindow_.end()) {
				//rendererRelations->second.decreaseRefrenceCount(); // TODO: clean up renderer by counter
				rendererToWindow_.erase(rendererRelations);
			}
			delete window->second;
			windows_.erase(window);
		}
	}

	void Scene::addEntity(std::string entityName, Entity* entity)
	{
		entities_[entityName] = entity;
	}

	Entity* Scene::getEntity(std::string entityName)
	{
		std::map<std::string, Entity*>::iterator it;
		it = entities_.find(entityName);
		if (it != entities_.end())
			return (it->second);
		else
			return nullptr;
	}

	void Scene::removeEntity(std::string entityName)
	{
		std::map<std::string, Entity*>::iterator it;
		it = entities_.find(entityName);
		if (it != entities_.end()) {
			delete it->second;
			entities_.erase(it);
		}
	}
}