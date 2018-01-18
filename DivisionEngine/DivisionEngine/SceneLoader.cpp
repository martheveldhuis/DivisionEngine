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
		bool sceneInJson = sceneJson.find("scene") != sceneJson.end();

		if (!sceneInJson ||
			(sceneJson["scene"].find("name") == sceneJson["scene"].end())) {
			sceneName = "scene1";
		}
		else {
			sceneName = sceneJson["scene"]["name"].get<std::string>();
		}

		Scene* scene1 = sceneManager_->createScene(sceneName);

		// Create the skybox's texture, or set default.
		std::string skyboxTexture = "skybox.bmp";

		if (sceneInJson && sceneJson["scene"].find("skybox_texture") !=
						   sceneJson["scene"].end()) {
			skyboxTexture = sceneJson["scene"]["skybox_texture"].
							get<std::string>();
		}
		Entity* skyBox = repository_->getSkyBox(resourceManager_);
		skyBox->setTexture(skyboxTexture);
		scene1->setSkyBox(skyBox);

		// Read terrain's heightmap and texture file names, or set defaults.
		std::string heightmap;
		std::string heightmapTexture;

		if (sceneInJson &&
			sceneJson["scene"].find("terrain") != sceneJson["scene"].end()) {

			if (sceneJson["scene"]["terrain"].find("heightmap") != 
				sceneJson["scene"]["terrain"].end()) {
				heightmap = sceneJson["scene"]["terrain"]["heightmap"].
							get<std::string>();
			}
			else {
				heightmap = "terrainhm.bmp";
			}

			if (sceneJson["scene"]["terrain"].find("texture") != 
				sceneJson["scene"]["terrain"].end()) {
				heightmapTexture = sceneJson["scene"]["terrain"]["texture"].
							get<std::string>();
			}
			else {
				heightmapTexture = "terrain.bmp";
			}

			// Create the terrain.
			Entity* terrain = repository_->getTerrain(heightmap, resourceManager_,
				heightmapTexture);
			terrain->setTexture(heightmapTexture);
			scene1->addEntity("terrain", terrain);
		}
		
		
		// Iterate over renderers in scene file.
		// TODO: put in separate function.
		Renderer* renderer = NULL;
		std::string rendererName;
		nlohmann::json renderersJson;

		if (sceneJson.find("renderers") == sceneJson.end()) {
			rendererName = "renderer1";
			renderer = sceneManager_->getRenderer(rendererName);

			if (!renderer) {
				renderer = repository_->getRenderer();
				renderer->setup();
				sceneManager_->addRenderer(rendererName, renderer);
			}
		}
		else {
			nlohmann::json::iterator renderersIterator = renderersJson.begin();
			nlohmann::json::iterator renderersEnd = renderersJson.end();

			for (; renderersIterator != renderersEnd; ++renderersIterator) {
				nlohmann::json rendererJson = (*renderersIterator);

				if (rendererJson.find("name") == rendererJson.end()) {
					rendererName = "renderer1";
				}
				else {
					rendererName = rendererJson["name"].get<std::string>();
				}

				renderer = sceneManager_->getRenderer(rendererName);

				if (!renderer) {
					renderer = repository_->getRenderer();
					renderer->setup();
					sceneManager_->addRenderer(rendererName, renderer);
				}
			}
		}


		// Iterate over windows in scene file.
		// TODO: put in separate function.
		std::string windowName;
		std::string windowTitle;
		std::string windowRenderer;

		if (sceneJson.find("windows") == sceneJson.end()) {
			windowName = "window1";
			windowTitle = "First window";
			windowRenderer = "renderer1";

			Entity* camera = repository_->getCamera(resourceManager_);
			Window* window = repository_->getWindow(windowTitle);
			Renderer* renderer = sceneManager_->getRenderer(windowRenderer);

			if (!renderer) {
				renderer = repository_->getRenderer();
				renderer->setup();
				sceneManager_->addRenderer(windowRenderer, renderer);
			}

			scene1->addWindow(windowName, window, renderer, camera);
		}
		else {

			nlohmann::json windowsJson = sceneJson["windows"];
			nlohmann::json::iterator windowsIterator = windowsJson.begin();
			nlohmann::json::iterator windowsEnd = windowsJson.end();

			for (; windowsIterator != windowsEnd; ++windowsIterator) {
				nlohmann::json windowJson = (*windowsIterator);
				nlohmann::json::iterator windowEnd = windowJson.end();

				if (windowJson.find("name") == windowEnd) {
					windowName = "window1";
				}
				else {
					windowName = windowJson["name"].get<std::string>();
				}
				
				if (windowJson.find("window_title") == windowEnd) {
					windowTitle = "First window";
				}
				else {
					windowTitle = windowJson["window_title"].get<std::string>();
				}

				if (windowJson.find("renderer") == windowEnd) {
					windowRenderer = "renderer1";
				}
				else {
					windowRenderer = windowJson["renderer"].get<std::string>();
				}
				
				Entity* camera = repository_->getCamera(resourceManager_);
				Window* window = repository_->getWindow(windowTitle);
				Renderer* renderer = sceneManager_->getRenderer(windowRenderer);

				if (!renderer) {
					renderer = repository_->getRenderer();
					renderer->setup();
					sceneManager_->addRenderer(windowRenderer, renderer);
				}

				scene1->addWindow(windowName, window, renderer, camera);
			}
		}


		// Iterate over entities in scene file.
		// TODO: put in function.
		std::string entityName;
		std::string entityMesh;
		std::string entityTexture;

		if (sceneJson.find("entities") != sceneJson.end()) {
			nlohmann::json entitiesJson = sceneJson["entities"];
			nlohmann::json::iterator entityIterator = entitiesJson.begin();
			nlohmann::json::iterator entitiesEnd = entitiesJson.end();

			for (; entityIterator != entitiesEnd; ++entityIterator) {
				nlohmann::json entityJson = (*entityIterator);
				nlohmann::json::iterator entityEnd = entityJson.end();

				Entity* entity1 = NULL;

				if (entityJson.find("name") == entityEnd) {
					entityName = "entity1";
				}
				else {
					entityName = entityJson["name"].get<std::string>();
				}

				if (entityJson.find("mesh") == entityEnd) {
					entityMesh = "tiger.x";
				}
				else {
					entityMesh = entityJson["mesh"].get<std::string>();
				}


				if (entityJson.find("pos") != entityEnd) {
					nlohmann::json pos = entityJson["pos"];
					nlohmann::json angle = entityJson["angle"];
					entity1 = new Entity(resourceManager_, pos["x"], pos["y"], 
										 pos["z"], angle["x"], angle["y"], 
										 angle["z"]);
				}

				if (!entity1)
					entity1 = new Entity(resourceManager_);

				scene1->addEntity(entityName, entity1);
				entity1->setMesh(entityMesh);

				if (entityJson.find("texture") != entityEnd) {
					entityTexture = entityJson["texture"].get<std::string>();
					entity1->setTexture(entityTexture);
				}
			}
		}

		return scene1;
	}
}