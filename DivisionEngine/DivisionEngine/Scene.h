#ifndef DIVISION_SCENE_H
#define DIVISION_SCENE_H

#include "Window.h"
#include "ResourceManager.h"

#include <map>
namespace Division {
	class Scene
	{
	private:
		std::map<std::string, Window*> windows_;
		ResourceManager* resourceManager_;
	public:
		Scene();
		Scene(ResourceManager*);
		~Scene();

		void addWindow(std::string, Window*);
		void getWindow(std::string, Window*);
		void removeWindow(std::string);
	};
}

#endif
