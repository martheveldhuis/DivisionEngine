#include "Kernel.h"
#include <map>

namespace Division
{
	Kernel::Kernel()
	{
	}

	Kernel::~Kernel()
	{
		delete repository_;
		delete resourceManager_;
		delete sceneManager_;
	}

	void Kernel::run()
	{
		Division::Win32Window* win = new Division::Win32Window("Window", "Window title");
		repository_ = new D3D9Repository();

		resourceManager_ = new ResourceManager(repository_->getTextureLoader(),
			repository_->getMeshLoader());

		sceneManager_ = new SceneManager(resourceManager_, repository_);

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
	}
}