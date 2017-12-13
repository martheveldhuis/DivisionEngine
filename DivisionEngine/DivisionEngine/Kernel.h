#ifndef DIVISION_KERNEL_H
#define DIVISION_KERNEL_H

#include "ResourceManager.h"
#include "SceneManager.h"
#include "WindowsInputManager.h"


namespace Division
{
	class Kernel
	{
	public:
		Kernel(Repository*);
		~Kernel();
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