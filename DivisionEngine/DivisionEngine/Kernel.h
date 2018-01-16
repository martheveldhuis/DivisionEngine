#ifndef DIVISION_KERNEL_H
#define DIVISION_KERNEL_H

#include <string>

#include "ResourceManager.h"
#include "Repository.h"
#include "SceneManager.h"

namespace Division
{
	enum RepositoryType { 
		REPOSITORYTYPE_D3D9, REPOSITORYTYPE_OPENGL
	};

	class Kernel
	{
	public:
		Kernel(RepositoryType = REPOSITORYTYPE_D3D9);
		~Kernel();
		void loadScene(std::string, std::string);
		void run();
		SceneManager* getSceneManager();
		ResourceManager* getResourceManager();
		Repository* getRepository();

	private:
		Repository* repository_;
		ResourceManager* resourceManager_;
		SceneManager* sceneManager_;
	};
}
#endif // !DIVISION_KERNEL_H