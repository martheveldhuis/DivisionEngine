#include "SceneLoader.h"

namespace Division
{

	SceneLoader::SceneLoader(SceneManager* sceneManager, Repository* d3D9Repository) 
	: d3D9Repository_(d3D9Repository), sceneManager_(sceneManager)
	{

	}


	SceneLoader::~SceneLoader()
	{
	}

	void SceneLoader::loadScene(std::string scene) {

		Renderer* renderer = d3D9Repository_->getRenderer();


		Division::Win32Window* win = new Division::Win32Window("Window", "Window title");

		Division::Entity* entity = new Division::Model(resourceManager, 0, 0, 0);
		entity->addMesh("tiger.x");
		std::map<std::string, Resource*> texture;
		texture["banana.bmp"] = entity->addTexture("banana.bmp");
		entity->getMesh("tiger.x")->setTextures(texture);

		Scene* currentScene = sceneManager_->createScene(scene, renderer);
		currentScene->addEntity("t", entity);
		currentScene->addWindow("Window", win);


	}

	void SceneLoader::parseHeightmap(std::string scene, std::string heightMap) {

		// this should come from the ??heightmaploader??


		const int width = 30;
		const int lenght = 30;

		DivisionVertex* vertices = new DivisionVertex[width * lenght];

		int index = 0;

		srand(GetTickCount64());
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < lenght; j++) {
				// maak random height value
				float y = (rand() % 300) / 100.0f; //max = 3.0

												   // maak grijswaarde gebaseerd op height val
				DWORD grayValB = int(y) * 80;
				DWORD grayValG = (int(y) * 80) << 8;
				DWORD grayValR = (int(y) * 80) << 16;
				int grayColor = grayValR + grayValG + grayValB;
				int x = i - width / 2 + 1;
				int z = j - lenght / 2 + 1;
				index = i * width + j;
				vertices[index] = { static_cast<float>(x), -y / 4 - .5f, static_cast<float>(z), 0xff000000 + grayColor };
			}
		}


		// new Terrain(vertices, width * lenght);
	}

}