#include "SceneLoader.h"

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

		Renderer* renderer = d3D9Repository_->getRenderer();

		Division::Win32Window* win = new Division::Win32Window("Window", "Window title");

		renderer->setHandle(win->getWindowHandle());
		renderer->setup();

		LPDIRECT3DDEVICE9 dev = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());

		Division::Entity* entity = new Model(resourceManager_, 5.0f, 5.0f, 5.0f);
		entity->addMesh("tiger.x");
		std::map<std::string, Resource*> texture;
		texture["banana.bmp"] = entity->addTexture("banana.bmp");
		entity->getMesh("tiger.x")->setTextures(texture);

		Scene* currentScene = sceneManager_->createScene(scene, renderer);
		currentScene->addEntity("t", entity);
		currentScene->addWindow("Window", win);

		Entity* terrain = d3D9Repository_->parseHeightmap("none", resourceManager_);
		currentScene->addEntity("terrain", terrain);
		

	}
}