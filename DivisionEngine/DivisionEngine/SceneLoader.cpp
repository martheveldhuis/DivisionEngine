#include "SceneLoader.h"
#include "Camera.h"
#include "SceneManager.h"


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
		
		std::string sceneName = sceneJson["scene"]["name"];
		std::string heightmap = sceneJson["scene"]["terrain"]["heightmap"];


		Scene* theScene = sceneManager_->createScene(scene);


		nlohmann::json renderersJson = sceneJson["renderers"];
		for (nlohmann::json::iterator it = renderersJson.begin(); it != renderersJson.end(); ++it) {
			nlohmann::json rendererJson = (*it);
			std::string name = rendererJson["name"];
			Renderer* renderer = sceneManager_->getRenderer(name);
			if (!renderer) {
				renderer = repository_->getRenderer();
				renderer->setup();
				sceneManager_->addRenderer(name, renderer);
			}
		}

		nlohmann::json windowsJson = sceneJson["windows"];
		for (nlohmann::json::iterator it = windowsJson.begin(); it != windowsJson.end(); ++it) {
			nlohmann::json windowJson = (*it);
			std::string name = windowJson["name"];
			std::string windowTitle = windowJson["window_title"];
			std::string renderer = windowJson["renderer"];
			Window* win = repository_->getWindow(windowTitle);
			theScene->addWindow(name, win, sceneManager_->getRenderer(renderer));
		}
		Camera* camera = new Camera(resourceManager_);

		Scene* theScene = sceneManager_->createScene(scene, renderer);
		theScene->addWindow("Window title", win, renderer, camera);

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

			theScene->addEntity(entity["name"], newEntity);
		}

		Entity* terrain = repository_->parseHeightmap(heightmap, resourceManager_);

		theScene->addEntity("terrain", terrain);

		return theScene;

	}
}