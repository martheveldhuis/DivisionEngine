#include "Kernel.h"

namespace Division
{
	Kernel::Kernel(Repository* repo) : repository_(repo)
	{
		resourceManager_ = new ResourceManager(repository_->getTextureLoader(),
			repository_->getMeshLoader());

		sceneManager_ = new SceneManager(resourceManager_, repository_);
	}

	Kernel::~Kernel()
	{
		delete repository_;
		delete resourceManager_;
		delete sceneManager_;
	}

	void Kernel::run()
	{
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
	SceneManager * Kernel::getSceneManager()
	{
		return sceneManager_;
	}
}