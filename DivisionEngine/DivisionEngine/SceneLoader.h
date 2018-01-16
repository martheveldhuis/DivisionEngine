#ifndef DIVISION_SCENELOADER_H
#define DIVISION_SCENELOADER_H

#include <string>

#include "Repository.h"
#include "ResourceManager.h"
#include "Scene.h"

namespace Division
{
	class SceneManager;

	/**
		Creates scenes from JSON files. The scenes created will contain
		each entity, window, renderer and camera specified in the loaded
		scene file.
	*/
	class SceneLoader
	{
	public:
		/**
			Create the scene loader.
			@param sceneManager Pass the scene manager to create a scene with.
			@param repository The repository to pull resources and entities from.
			@param resourceManager The resource manager to get meshes and textures.
		*/
		SceneLoader(SceneManager*, Repository*, ResourceManager*);
		~SceneLoader();
		/**
			Loads a scene from a JSON scene file.
			@param scene The name of the scene as it will be stored in the scene manager.
			@param filename The file to load the configuration from.
			@returns The filled scene file.
		*/
		Scene* loadScene(std::string filename);
	private:
		Repository* repository_;
		ResourceManager* resourceManager_;
		SceneManager* sceneManager_;
	};
}
#endif // ! DIVISION_SCENELOADER_H