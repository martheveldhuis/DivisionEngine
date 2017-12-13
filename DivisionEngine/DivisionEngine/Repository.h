#ifndef DIVISION_REPOSITORY_H
#define DIVISION_REPOSITORY_H

#include <string>

#include "ResourceLoader.h"
#include "Renderer.h"
#include "Entity.h"
#include "Window.h"
#include "InputManager.h"

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
			@returns void*
		*/
		virtual void* getFrameworkInterface() = 0;
		/**
			Creates a texture loader to convert files to generic Texture
			classes.
			@returns ResourceLoader*
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
			@returns Entity*
		*/
		virtual Entity* parseHeightmap(std::string, ResourceManager*) = 0;
		/**
			Creates a window from a string.
			@returns Window*
		*/
		virtual Window* getWindow(std::string) = 0;
		/**
			Creates a framework specific input manager for handling input.
			@returns An input manager
		*/
		virtual InputManager* getInputManager() = 0;
	};
}

#endif // ! DIVISION_REPOSITORY_H