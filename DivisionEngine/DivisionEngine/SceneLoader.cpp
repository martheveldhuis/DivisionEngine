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

		Division::Win32Window* win = new Division::Win32Window("Window title1");
		Division::Win32Window* win2 = new Division::Win32Window("Window title2");

		renderer->setHandle(win->getWindowHandle());
		renderer->setup();

		LPDIRECT3DDEVICE9 dev = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());

		Scene* theScene = sceneManager_->createScene(scene, renderer);

		theScene->addWindow("Window1", win, renderer);
		theScene->addWindow("Window2", win2, renderer);


		std::list<Entity*> entitylist1;

		Entity* entity = new Model(resourceManager_, 1.0f, 1.0f, 1.0f); // TODO: put this in a function
		entity->addMesh("tiger.x");
		std::map<std::string, Resource*> texture;
		texture["banana.bmp"] = entity->getTexture("banana.bmp");
				
		Entity* entity2 = new Model(resourceManager_);
		entity2->addMesh("tiger.x");

		Entity* terrain = d3D9Repository_->parseHeightmap("none", resourceManager_);

		entitylist1.push_back(entity);
		entitylist1.push_back(entity2);
		entitylist1.push_back(terrain);

		theScene->addEntityList("entityList1", entitylist1, win);
		theScene->addEntityList("entityList1", entitylist1, win2);


	}
}