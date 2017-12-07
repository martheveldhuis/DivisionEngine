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

		Scene* scene = sceneManager_->loadScene("tst");
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
			}

		}
		delete win;
		delete renderer;
		delete resourceManager;
		delete entity;
	}
}