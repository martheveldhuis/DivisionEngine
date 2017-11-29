// DivisionGame.cpp : Defines the entry point for the console application.
//
#include "DivisionEngine.h"
#include "Win32Window.h"
//#include "D3D9Renderer.h"
#include <iostream>

int main()
{
	Division::DivisionEngine Engine;
	Division::ResourceManager ResourceManger;
	Division::SceneManager SceneManager;

	Engine.getResourceManager(&ResourceManger);
	Engine.getSceneManager(&SceneManager);

	//SceneManager.createScene("Test Scene");
	//Scene Test;
	//SceneManager.getScene("Test Scene", &Test);
	//Test.addWindow("Window", new Win32Window("Window", "Window title"));
	//Win32Window win;
	//Test.getWindow("Window", &win);

	//SceneManager.addRenderer("DXRenderer", new Division::D3D9Renderer(NULL, NULL, win.getWindowHandle()));

	while (true) {
	}

	return 0;
}