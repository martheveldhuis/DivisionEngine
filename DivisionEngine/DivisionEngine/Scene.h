#ifndef DIVISION_SCENE_H
#define DIVISION_SCENE_H

#include <map>
#include <string>

#include "Entity.h"
#include "Renderer.h"
#include "Window.h"
#include "ResourceManager.h"
#include "InputManager.h"

namespace Division
{
	/**
		A scene in which the entities , windows and camera are stored, renders these objects to the renderer when called.
	*/
	class Scene
	{
	public:
		/**
			Create the scene.
			@param resourcemanager The resource manager to add entities to the scene
			@param inputmanager Pass the input manager to handle user input for each window.
		*/
		Scene(ResourceManager* resourcemanager, InputManager* inputmanager);
		/**
			Clean up the scene
			@todo Proper cleanup off the entities and windows.
		*/
		~Scene();
		/**
			Renders all entities on each window from the perspective of the attached camera with the designated renderer.
		*/
		void render();
		/**
			Add a window to the scene.
			@param windowName The name the window that will be added to the scene.
			@param window The window that needs to be added to the scene.
			@param renderer The renderer that the window will render on.
			@param camera The entity that will determine the perspective the window will show.			
		*/
		void addWindow(std::string windowName, Window* window, Renderer* renderer, Entity* camera);
		/**
			Get a window stored in the scene.
			@param windowName The name of the window in the scene you want to retrieve.
			@returns A pointer to the window.		
		*/
		Window* getWindow(std::string windowName);
		/**
			Remove a window from the scene
			@param windowName The name of the window in the scene you want to remove.		
		*/
		void removeWindow(std::string windowName);
		/**
			Create entity and adds it to the scene.
			@param entityName The name the entity that will be added to the scene.
			@param x The x location of the entity, default 0.
			@param y The y location of the entity, default 0.
			@param z The z location of the entity, default 0.
			@param x The x angle of the entity, default 0.
			@param y The y angle of the entity, default 0.
			@param z The z angle of the entity, default 0.
			@returns The entity that has been added to the scene.
		*/
		Entity* createEntity(std::string entityName,
			float x = 0, float y = 0, float z = 0, float xAngle = 0, float yAngle = 0, float zAngle = 0	);
		/**
			Add a entity to the scene.
			@param entityName The name the entity that will be added to the scene.
			@param entity The entity that needs to be added to the scene.
		*/
		void addEntity(std::string entityName, Entity* entity);
		/**
			Get a entity stored in the scene.
			@param entityName The name of the entity in the scene you want to retrieve.
			@returns A pointer to the entity.
		*/
		Entity* getEntity(std::string entityName);
		/**
			Remove a entity from the scene
			@param entityName The name of the entity in the scene you want to remove.
		*/
		void removeEntity(std::string entityName);
	private:
		ResourceManager* resourceManager_;
		InputManager* inputManager_;
		Entity* skyBox_;
		std::map<std::string, Entity*> entities_;
		std::map<std::string, Window*> windows_;
		std::map<Window*, Renderer*> rendererToWindow_; /*!< Map of renderer bindings to windows */
		std::map<Window*, Entity*> cameraToWindow_;  /*!< Map of camera bindings to windows */
	};
}

#endif
