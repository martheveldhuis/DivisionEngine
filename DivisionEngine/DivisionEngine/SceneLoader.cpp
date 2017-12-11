#include "SceneLoader.h"
#include "json.hpp"
#include <string>

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

		Scene* theScene = sceneManager_->createScene(scene, renderer);
		theScene->addWindow("Window title", win, renderer);

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


			newEntity->addMesh((*it)["mesh"]);
			if (entity.find("texture") != entity.end()) {
				std::string customTexture = entity["texture"];

				if (!customTexture.empty()) {
					std::map<std::string, Resource*> texture;
					texture[customTexture] = newEntity->getTexture(customTexture);
				}
			}

			entitylist1.push_back(newEntity);
		}

		Entity* terrain = d3D9Repository_->parseHeightmap(heightmap, resourceManager_);

		entitylist1.push_back(terrain);

		theScene->addEntityList("entityList1", entitylist1, win);
		

	}
}