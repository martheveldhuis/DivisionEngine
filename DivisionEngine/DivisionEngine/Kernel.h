#ifndef DIVISION_KERNEL_H
#define DIVISION_KERNEL_H

#include <string>


namespace Division
{
	class ResourceManager;
	class Repository;
	class SceneManager;
	class Kernel
	{
	public:
		Kernel();
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