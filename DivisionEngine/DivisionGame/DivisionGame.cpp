// DivisionGame.cpp : Defines the entry point for the console application.
//
#include <iostream>

#include "DivisionEngine.h"
#include "Win32Window.h"
//#include "D3D9Renderer.h"
#include "WindowsInputManager.h"
#include "LoggerPool.h"
#include "TextureLoader.h"
#include "MeshLoader.h"

int main()
{
	Division::DivisionEngine Engine;
	Division::ResourceManager ResourceManger;
	Division::SceneManager SceneManager;

	Engine.getResourceManager(&ResourceManger);
	Engine.getSceneManager(&SceneManager);


	Division::Win32Window* win = new Division::Win32Window("Window", "Window title");
	Division::Renderer* renderer = new Division::D3D9Renderer(NULL, NULL, win->getWindowHandle());

	// For testing the textureloader.
	Division::TextureLoader* textureloader = new Division::TextureLoader();
	LPDIRECT3DTEXTURE9 bananaTexture = textureloader->getTexture("banana.bmp");

	// For testing the meshloader.
	Division::MeshLoader* meshloader = new Division::MeshLoader();
	LPD3DXMESH tigerMesh = meshloader->getMesh("tiger.x");
	SceneManager.addRenderer("re", renderer);

	Division::Scene* Test;

	Test = SceneManager.createScene("Test Scene", renderer);
	Test->addWindow("Window", win);






	while (true) {
		Test->begin();
	}

	return 0;
}