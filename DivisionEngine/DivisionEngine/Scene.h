#ifndef DIVISION_SCENE_H
#define DIVISION_SCENE_H

#include "Window.h"
#include "WindowsWindow.h"

#include <map>

class Scene
{
private:
	std::map<std::string, Window*> windows_;
public:
	void addWindow(std::string, Window*);
	void getWindow(std::string, Window*);
	void removeWindow(std::string);
	Scene();
	~Scene();
};

#endif
