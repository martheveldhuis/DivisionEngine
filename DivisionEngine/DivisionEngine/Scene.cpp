#include "Scene.h"

#include "D3D9Camera.h"
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

			Entity* camera = cameraToWindow_[windowIt->second];

			// Only update the camera based on input on the active window.
			if (windowIt->second->getWindowHandle() == inputManager_->getWindowHandle()) {
				InputStates i = inputManager_->getInput();
				camera->updateOrientation(&i);
			}
			else {
				// Else update with empty input to still render this window.
				InputStates i;
				camera->updateOrientation(&i);
			}

			std::map<Window*, Renderer*>::const_iterator rendererIt;
			rendererIt = rendererToWindow_.find(windowIt->second);

			if (rendererIt == rendererToWindow_.end()) {
				LoggerPool::getInstance()->getLogger("scene")
					->logError("No renderers found while trying to render");
				return;
			}

			// Set the camera orientation on the renderer.
			rendererIt->second->setCameraMatrix(camera->getOrientation());

			// Set the skybox position (the first entity) based on the camera
			// position.
			Position skyboxPosition;
			skyboxPosition.xAngle = 0;
			skyboxPosition.zAngle = 0;
			skyboxPosition.yAngle = 0;
			skyboxPosition.xPosition = camera->getPosition().xPosition;
			skyboxPosition.yPosition = camera->getPosition().yPosition;
			skyboxPosition.zPosition = camera->getPosition().zPosition;
			rendererIt->second->setWorldMatrix(&skyboxPosition);

			rendererIt->second->clear();
			rendererIt->second->beginScene();

			std::map<std::string, Entity*>::const_iterator entityIt = entities_.begin();
			std::map<std::string, Entity*>::const_iterator enititiesEnd = entities_.end();

			// Render all the entities in the scene.
			for (; entityIt != enititiesEnd; entityIt++) {
				entityIt->second->render(rendererIt->second);
			}

			rendererIt->second->endScene();
			rendererIt->second->present(windowIt->second->getWindowHandle());
		}
	}

	void Scene::addWindow(std::string windowName, Window* window, Renderer* renderer, Entity* camera)
	{
		windows_[windowName] = window;
		rendererToWindow_[window] = renderer;
		renderer->increaseReferenceCount();
		cameraToWindow_[window] = camera;
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
				rendererRelations->second->decreaseReferenceCount();
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