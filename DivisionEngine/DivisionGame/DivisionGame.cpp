// DivisionGame.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "Kernel.h"
#include "D3D9Camera.h"


//int main()
//{
//	// Simple interface
//
//	Division::Kernel divisionEngine;
//
//	divisionEngine.loadScene("scene1", "scenefile.json");
//	//	divisionEngine.loadScene("scene2", "scenefile2.json");
//	divisionEngine.run();
//	
//	return 0;
//}

int main()
{
	// Sanbox interface

	Division::Kernel divisionEngine(Division::D3D9);
	Division::ResourceManager* resourceManager = divisionEngine.getResourceManager();
	Division::SceneManager* sceneManager = divisionEngine.getSceneManager();
	Division::Repository* repository = divisionEngine.getRepository();

	Division::Scene* scene = sceneManager->createScene("scene2");
	
	Division::Window* window = repository->getWindow("window2");
	Division::Renderer* renderer = repository->getRenderer();
	renderer->setup();
	Division::D3D9Camera* camera = new Division::D3D9Camera(resourceManager);
	
	scene->addWindow("window2", window, renderer, camera);
	sceneManager->addRenderer("renderer", renderer);

	Division::Entity* tiger = new Division::Entity(resourceManager);
	tiger->setMesh("tiger.x");


	Division::Entity* skyBox = repository->getSkyBox(resourceManager);
	skyBox->setTexture("cubemaplayout.png");
	scene->addEntity("skybox", skyBox);

	scene->addEntity("tiger1", tiger);


	divisionEngine.run();

	return 0;
}