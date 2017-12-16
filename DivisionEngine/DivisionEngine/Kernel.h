#ifndef DIVISION_KERNEL_H
#define DIVISION_KERNEL_H

#include <string>

#include "ResourceManager.h"
#include "WindowsInputManager.h"
#include "Repository.h"
#include "SceneManager.h"

namespace Division
{
	class Kernel
	{
	public:
		Kernel(Repository*);
		~Kernel();
		void loadScene(std::string, std::string);
		void run();
		SceneManager* getSceneManager();
		ResourceManager* getResourceManager();
		

	private:
		Repository* repository_;
		ResourceManager* resourceManager_;
		SceneManager* sceneManager_;
	};
}
#endif // !DIVISION_KERNEL_H