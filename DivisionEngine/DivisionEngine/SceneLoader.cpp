#include "SceneLoader.h"

#include <string>
#include <fstream>

#include "json.hpp"

namespace Division
{

	SceneLoader::SceneLoader(SceneManager* sceneManager,
		Repository* d3D9Repository, ResourceManager* resourceManager) 
	: repository_(d3D9Repository), sceneManager_(sceneManager),
	resourceManager_(resourceManager)
	{

	}


	SceneLoader::~SceneLoader()
	{
	}

	Scene* SceneLoader::loadScene(std::string scene, std::string filename) {

		std::ifstream i(filename);
		nlohmann::json sceneJson;
		i >> sceneJson;
		
		std::string heightmap = sceneJson["terrain"]["heightmap"];

		Renderer* renderer = sceneManager_->getRenderer("test");
		if (!renderer) {
			renderer = repository_->getRenderer();
			renderer->setup();
			sceneManager_->addRenderer("test", renderer);
		}

		

		Window* win = repository_->getWindow(scene + ".1");

		Window* win2 = repository_->getWindow(scene + ".2");

		Scene* theScene = sceneManager_->createScene(scene, renderer);
		theScene->addWindow(scene + ".1" + "Window", win, renderer);
		theScene->addWindow(scene + ".2" + "Window", win2, renderer);

		nlohmann::json objectJson = sceneJson["game_objects"];

		std::list<Entity*> entitylist1;

		int objectCount = 0;
		for (nlohmann::json::iterator it = objectJson.begin(); it != objectJson.end(); ++it) {
			nlohmann::json entity = (*it);
			nlohmann::json pos = entity["pos"];
			nlohmann::json angle = entity["angle"];

			Entity* newEntity = new Entity(
				resourceManager_, pos["x"], pos["y"], pos["z"],
				angle["x"], angle["y"], angle["z"]);

			newEntity->setMesh((*it)["mesh"]);

			if (entity.find("texture") != entity.end()) {
				std::string customTexture = entity["texture"];

				if (!customTexture.empty()) {
					newEntity->setTexture(customTexture);
				}
			}

			entitylist1.push_back(newEntity);
		}

		Entity* terrain = repository_->parseHeightmap(heightmap, resourceManager_);

		entitylist1.push_back(terrain);

		theScene->addEntityList("entityList1", entitylist1, win);
		theScene->addEntityList("entityList1", entitylist1, win2);

		return theScene;

	}
}