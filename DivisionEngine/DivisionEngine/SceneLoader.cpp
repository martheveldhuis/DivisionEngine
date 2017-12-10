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
		Division::Win32Window* win2 = new Division::Win32Window("Window2", "Window title2");

		renderer->setHandle(win->getWindowHandle());
		renderer->setup();

		LPDIRECT3DDEVICE9 dev = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());

		Scene* theScene = sceneManager_->createScene(scene, renderer);
		theScene->addWindow("Window title", DivisionWindow(win, renderer));
		theScene->addWindow("Window title2", DivisionWindow(win2, renderer));

		Entity* entity = new Model(resourceManager_, 5.0f, 5.0f, 5.0f); // TODO: put this in a function
		entity->addMesh("tiger.x");
		std::map<std::string, Resource*> texture;
		texture["banana.bmp"] = entity->getTexture("banana.bmp");
		entity->getMesh("tiger.x")->setTextures(texture);
				
		Entity* entity2 = new Model(resourceManager_, 5.0f, 5.0f, 5.0f); // TODO: fix
		entity2->addMesh("tiger.x");

		theScene->addEntity("t", DivisionEntity(entity, win));
		theScene->addEntity("t2", DivisionEntity(entity2, win2));

		Entity* terrain = d3D9Repository_->parseHeightmap("none", resourceManager_);
		theScene->addEntity("terrain", DivisionEntity(terrain, win2));
		

	}
}