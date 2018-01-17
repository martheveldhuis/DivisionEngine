#ifndef DIVISION_KERNEL_H
#define DIVISION_KERNEL_H

#include <string>

#include "ResourceManager.h"
#include "Repository.h"
#include "SceneManager.h"

namespace Division
{
	/**
		Enumeration for selection the repository type .
	*/
	enum RepositoryType { 
		REPOSITORYTYPE_D3D9, REPOSITORYTYPE_OPENGL
	};
	/**
		Entry point for the engine.
	*/
	class Kernel
	{
	public:
		/**
			Create the kernel.
			@param repoType The type of repository too be selected by the kernel.
		*/
		Kernel(RepositoryType repoType = REPOSITORYTYPE_D3D9);
		/**
			Clean up the kernel.
		*/
		~Kernel();
		/**
			Proxy function for loading scenes via the simple interface.
		*/
		void loadScene(std::string, std::string);
		/**
			Main run cycle handles OS messages and input handle switching.
		*/
		void run();
		/**
			Get scene manager.
			@return The scene manager.
		*/
		SceneManager* getSceneManager();
		/**
			Get ResourceManager.
			@return The ResourceManager.
		*/
		ResourceManager* getResourceManager();
		/**
			Get repository.
			@return The repository.
		*/
		Repository* getRepository();
	private:
		Repository* repository_;
		ResourceManager* resourceManager_;
		SceneManager* sceneManager_;
	};
}
#endif // !DIVISION_KERNEL_H