#include "DivisionEngine.h"
#include "Win32Window.h"
#include "WindowsInputManager.h"
#include "Model.h"
#include "D3D9Renderer.h"

#include <map>

namespace Division 
{
	DivisionEngine::DivisionEngine()
	{
	}

	DivisionEngine::~DivisionEngine()
	{
		delete resourceManager_;
		delete sceneManager_;
	}

	void DivisionEngine::run()
	{
		sceneManager_ = new SceneManager();

		// TODO: make sure all 'new' objects get managed properly
		Division::Win32Window* win = new Division::Win32Window("Window", "Window title");
		Division::D3D9Renderer* renderer = new Division::D3D9Renderer(NULL, NULL, win->getWindowHandle());

		LPDIRECT3DDEVICE9 dev = static_cast<LPDIRECT3DDEVICE9>(renderer->getDevice());
		Division::ResourceManager* resourceManager = new Division::ResourceManager(dev);

		Division::Entity* entity = new Division::Model(resourceManager, 0,0,0);
		entity->addMesh("tiger.x");
		std::map<std::string, Resource*> texture;
		texture["banana.bmp"] = entity->addTexture("banana.bmp");
		entity->getMesh("tiger.x")->setTextures(texture);

		Division::Scene* scene;
		scene = sceneManager_->createScene("Test Scene", renderer);
		scene->addEntity("t", entity);
		scene->addWindow("Window", win);

		HWND window = win->getWindowHandle();
		Division::WindowsInputManager* windowsInputManager = &(Division::WindowsInputManager::getInstance(&window));

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {

				scene->begin();

				Division::InputStates inputStates = windowsInputManager->getInput();
				if (inputStates.moveForward)
					MessageBox(0, "moving forward", "alert", MB_OK);
				if (inputStates.action)
					MessageBox(0, "action", "alert", MB_OK);
			}

		}
		/*delete win;
		delete renderer;
		delete resourceManager;
		delete entity;*/
	}
}