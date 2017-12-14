#include "SceneLoader.h"
#include "Camera.h"
#include "SceneManager.h"

#include <string>
#include <fstream>

#include "json.hpp"

namespace Division
{

	SceneLoader::SceneLoader(SceneManager* sceneManager,
		Repository* d3D9Repository, ResourceManager* resourceManager) 
	: d3D9Repository_(d3D9Repository), sceneManager_(sceneManager),
	resourceManager_(resourceManager)
	{

	}


	SceneLoader::~SceneLoader()
	{
	}

	void SceneLoader::loadScene(std::string scene) {

		std::ifstream i("scenefile.json");
		nlohmann::json sceneJson;
		i >> sceneJson;
		
		std::string heightmap = sceneJson["terrain"]["heightmap"];

		Renderer* renderer = d3D9Repository_->getRenderer();

		Window* win = d3D9Repository_->getWindow("Division");

		renderer->setHandle(win->getWindowHandle());
		renderer->setup();

		Camera* camera = new Camera(resourceManager_);

		Scene* theScene = sceneManager_->createScene(scene, renderer);
		theScene->addWindow("Window title", win, renderer, camera);

		nlohmann::json objectJson = sceneJson["game_objects"];

		std::list<Entity*> entitylist1;

		int objectCount = 0;
		for (nlohmann::json::iterator it = objectJson.begin(); it != objectJson.end(); ++it) {
			nlohmann::json entity = (*it);
			nlohmann::json pos = entity["pos"];
			nlohmann::json angle = entity["angle"];

			Entity* newEntity = new Model(
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


		Entity* terrain = d3D9Repository_->parseHeightmap(heightmap, resourceManager_);

		entitylist1.push_back(terrain);

		theScene->addEntityList("entityList1", entitylist1, win);
		

	}
}