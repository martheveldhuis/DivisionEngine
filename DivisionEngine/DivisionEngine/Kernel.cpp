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
		repository_ = new D3D9Repository();

		resourceManager_ = new ResourceManager(repository_->getTextureLoader(),
			repository_->getMeshLoader());

		sceneManager_ = new SceneManager(resourceManager_, repository_);

		Scene* scene = sceneManager_->loadScene("scene1", "scenefile.json");
		Scene* scene2 = sceneManager_->loadScene("scene2", "scenefile2.json");

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

				sceneManager_->renderScenes();
			}

		}
	}
}