#ifndef DIVISION_SCENEMANAGER_H
#define DIVISION_SCENEMANAGER_H

#include "Renderer.h"
#include "Scene.h"

#include <map>

class SceneManager
{
private:
	std::map<std::string, Renderer*> renderers_;
	std::map<std::string, Scene*> scenes_;
public:
	void addRenderer(std::string, Renderer*);
	void getRenderer(std::string, Renderer*);
	void removeRenderer(std::string);

	void addScene(std::string, Scene*);
	void createScene(std::string);
	void getScene(std::string, Scene*);
	void removeScene(std::string);

	SceneManager();
	~SceneManager();
};

#endif