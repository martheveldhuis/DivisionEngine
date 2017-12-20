#ifndef DIVISION_REPOSITORY_H
#define DIVISION_REPOSITORY_H

#include <string>

#include "ResourceLoader.h"
#include "Renderer.h"
#include "Entity.h"
#include "Window.h"
#include "InputManager.h"
#include "SkyBox.h"

/**
	Generates framework specific objects. On instianciation one framework
	interface class will be created to build
*/
namespace Division
{
	class Repository
	{
	public:
		~Repository() {};
		/**
			Gets the core framework object to instanciate classes.
		*/
		virtual void* getFrameworkInterface() = 0;
		/**
			Creates a texture loader to convert files to generic Texture
			classes.
			@returns A reference to a new TextureLoader
		*/
		virtual ResourceLoader* getTextureLoader() = 0;
		/**
			Creates a mesh loader to convert files to generic Mesh classes.
			@returns ResourceLoader*
		*/
		virtual ResourceLoader* getMeshLoader() = 0;
		/**
			Creates a renderer to communicate the device.
			@returns Renderer*
		*/
		virtual Renderer* getRenderer() = 0;
		/**
			Parses a heightmap and stores the data in a Terrain.
			@param filename The file to retrieve the heightmap data from.
			@param rm ResourceManager to be passed to the class for texture loading.
			@returns A Terrain object which can be renderered.
		*/
		virtual Entity* getTerrain(std::string, ResourceManager*, std::string) = 0;
		/**
			Creates a window from a string.
			@param title The window title.
			@returns A Window object with requested options.
		*/
		virtual Window* getWindow(std::string) = 0;
		/**
			Creates a framework specific input manager for handling input.
			@returns An input manager
		*/
		virtual InputManager* getInputManager() = 0;
		/**
			Creates a sky box with a 1x1x1 dimension.
			@param rm ResourceManager to be passed to the class for texture loading.
			@return The created sky box.
		*/
		virtual Entity* getSkyBox(ResourceManager* rm) = 0;
	};
}

#endif // ! DIVISION_REPOSITORY_H