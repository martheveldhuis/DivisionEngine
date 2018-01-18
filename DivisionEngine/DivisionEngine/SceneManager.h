#ifndef DIVISION_SCENEMANAGER_H
#define DIVISION_SCENEMANAGER_H

#include <map>

#include "Renderer.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Repository.h"
#include "InputManager.h"

namespace Division
{
	class SceneLoader;
	/**
		Manages the scenes by either loading them through the scene loader or creating them
		Stores the renderer's for use by the scenes. 
	*/
	class SceneManager
	{
	public:
		/**
			Create a scene manger 
			@param resourceManager The resource manager to add to scenes and scene loaders
			@param repository The repository to pull resources.
		*/
		SceneManager(ResourceManager* rescourcemanager, Repository* repository);
		/**
			Clean up the scene manager
			@todo Proper cleanup off the entities and windows.
		*/
		~SceneManager();
		/**
			Renders all scenes in the manager 
		*/
		
		void renderScenes();
		/**
			Set the handle of the input manager to the provided handle.
			@param handle The handle that will be set on inputManager_
		*/
		void setInputHandle(void* handle);
		/**
			Get the handle currently set on the inputManagers
			@returns The handle of inputManager_
		*/
		void* getInputHandle();

		/**
			Add renderer to the scene manager
			@param rendererName The name the renderer that will be added to the scene manager. 
			@param renderer The renderer that needs to be added to the scene manger.
		*/
		void addRenderer(std::string rendererName, Renderer* renderer);
		/**
			Get a window stored in the scene manager.
			@param rendererName The name of the renderer you want to retrieve.
			@returns A pointer to the renderer.
		*/
		Renderer* getRenderer(std::string rendererName);
		/**
			Remove a renderer from the scene manager
			@param rendererName The name of the renderer in the scene manager you want to remove.
		*/
		void removeRenderer(std::string rendererName);

		/**
			Create scene and adds it to the scene manager.
			@param sceneName The name the scene that will created.
			@returns The scene that has been added to the scene manager.
		*/
		Scene* createScene(std::string sceneName);
		/**
			Load a scene via the scene loader.
			@param sceneName The name the scene that will loaded and added.
			@param sceneFileName The name of the file that will be loaded.
			@returns The scene that has been added to the scene manager.
		*/
		Scene* loadScene(std::string sceneName, std::string sceneFileName);
		/**
			Get a scene from the scene manager.
			@param sceneName The name the scene that you want to retrieve.
			@returns The scene that has been added to the scene manager.
		*/
		Scene* getScene(std::string sceneName);
		/**
			Remove a scene from the scene manger
			@param sceneName The name of the scene in the scene manager you want to remove.
		*/
		void removeScene(std::string sceneName);
	private:
		std::map<std::string, Renderer*> renderers_;
		std::map<std::string, Scene*> scenes_;
		ResourceManager* resourceManager_;
		InputManager* inputManager_;
		Repository* repository_;
		SceneLoader* sceneLoader_;
	};
}

#endif