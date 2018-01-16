#include "SceneLoader.h"
#include "SceneManager.h"
#include "Model.h"

#include "json.hpp"
#include <fstream>

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

	Scene* SceneLoader::loadScene(std::string filename) {

		// Open the scene file into a json object.
		std::ifstream fileStream(filename);
		nlohmann::json sceneJson;
		fileStream >> sceneJson;
		
		// Read the scene name, or set default.
		std::string sceneName;
		if ((sceneJson.find("scene") == sceneJson.end()) ||
			(sceneJson["scene"].find("name") == sceneJson["scene"].end())) {
			sceneName = "scene1";
		}
		else {
			sceneName = sceneJson["scene"]["name"].get<std::string>();
		}

		Scene* scene1 = sceneManager_->createScene(sceneName);

		// Read the terrain's heightmap file name, or set default.
		std::string heightmap = sceneJson["scene"]["terrain"]["heightmap"];
		if (heightmap.empty())
			heightmap = "terrainhm.bmp";

		// Read the terrain's heightmap texture file name, or set default.
		std::string heightmapTexture = sceneJson["scene"]["terrain"]["texture"];
		if (heightmapTexture.empty())
			heightmapTexture = "terraintexture.bmp";

		// Create the terrain.
		Entity* terrain = repository_->getTerrain(heightmap, resourceManager_, heightmapTexture);
		terrain->setTexture(heightmapTexture);
		scene1->addEntity("terrain", terrain);

		// Create the skybox with default.
		// TODO: implement skybox in scene file.
		Entity* skyBox = repository_->getSkyBox(resourceManager_);
		skyBox->setTexture("skybox.png");
		scene1->addEntity("skybox", skyBox);

		// Iterate over renderers in scene file.
		nlohmann::json renderersJson = sceneJson["renderers"];
		nlohmann::json::iterator renderersIterator = renderersJson.begin();
		nlohmann::json::iterator renderersEnd = renderersJson.end();
		Renderer* renderer = NULL;
		int renderNr = 1;

		for (; renderersIterator != renderersEnd; ++renderersIterator, 
			 ++renderNr) {
			nlohmann::json rendererJson = (*renderersIterator);
			std::string rendererName = rendererJson["name"];

			// Make sure renderers get names.
			if (rendererName.empty())
				rendererName = "renderer" + renderNr;

			renderer = sceneManager_->getRenderer(rendererName);

			if (!renderer) {
				renderer = repository_->getRenderer();
				renderer->setup();
				sceneManager_->addRenderer(rendererName, renderer);
			}
		}

		nlohmann::json windowsJson = sceneJson["windows"];
		for (nlohmann::json::iterator it = windowsJson.begin(); it != windowsJson.end(); ++it) {
			nlohmann::json windowJson = (*it);
			std::string name = windowJson["name"];
			std::string windowTitle = windowJson["window_title"];
			std::string renderer = windowJson["renderer"];

			// TODO: add new entity with camera mesh to entities.
			Entity* camera = repository_->getCamera(resourceManager_);
			Window* win = repository_->getWindow(windowTitle);
			scene1->addWindow(name, win, (sceneManager_->getRenderer(renderer)), camera);
		}

		nlohmann::json objectJson = sceneJson["game_objects"];
		for (nlohmann::json::iterator it = objectJson.begin(); it != objectJson.end(); ++it) {
			nlohmann::json entity = (*it);
			nlohmann::json pos = entity["pos"];
			nlohmann::json angle = entity["angle"];

			Entity* newEntity = new Entity(
				resourceManager_, pos["x"], pos["y"], pos["z"],
				angle["x"], angle["y"], angle["z"]);

			newEntity->setMesh(entity["mesh"]);

			if (entity.find("texture") != entity.end()) {
				std::string customTexture = entity["texture"];

				if (!customTexture.empty()) {
					newEntity->setTexture(customTexture);
				}
			}

			scene1->addEntity(entity["name"], newEntity);
		}


		return scene1;

	}
}