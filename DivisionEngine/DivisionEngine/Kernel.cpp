#include "Kernel.h"

#include "D3D9Repository.h"

#include "ResourceManager.h"
#include "Repository.h"
#include "SceneManager.h"

namespace Division
{
	Kernel::Kernel()
	{
		repository_ = new D3D9Repository();

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

	void Kernel::loadScene(std::string scene, std::string fileName)
	{
		sceneManager_->loadScene(scene, fileName);
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

	SceneManager* Kernel::getSceneManager()
	{
		return sceneManager_;
	}

	ResourceManager * Kernel::getResourceManager()
	{
		return resourceManager_;
	}
}