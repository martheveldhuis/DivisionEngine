// DivisionGame.cpp : Defines the entry point for the console application.
//
#include "DivisionEngine.h"
#include "Win32Window.h"
//#include "D3D9Renderer.h"
#include "WindowsInputManager.h"
#include "LoggerPool.h"
#include <iostream>

int main()
{
	Division::DivisionEngine Engine;
	Division::ResourceManager ResourceManger;
	Division::SceneManager SceneManager;

	Engine.getResourceManager(&ResourceManger);
	Engine.getSceneManager(&SceneManager);


	Division::Win32Window* win = new Division::Win32Window("Window", "Window title");
	Division::Renderer* renderer = new Division::D3D9Renderer(NULL, NULL, win->getWindowHandle());

	SceneManager.addRenderer("re", renderer);

	Division::Scene* Test;

	Test = SceneManager.createScene("Test Scene", renderer);
	Test->addWindow("Window", win);


	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			Test->begin();
	}

	return 0;
}