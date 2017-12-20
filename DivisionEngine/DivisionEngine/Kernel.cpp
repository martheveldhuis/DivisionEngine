#include "Kernel.h"

#include "Clock.h"
#include "LoggerPool.h"
#include "D3D9Repository.h"

namespace Division
{
	Kernel::Kernel(repositoryType repoType)
	{
		switch (repoType)
		{
		case D3D9:
			repository_ = new D3D9Repository();
			break;
		case OPENGL:

			break;
		default:

			break;
		}		

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
		Clock clock;
		
		Logger* kernelLog = LoggerPool::getInstance()->getLogger("clock");

		clock.start();
		int frames = 0;
		int lastSec = 0;
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				frames++;
				if (clock.getRuntime() / 1000 != lastSec) {
					lastSec = clock.getRuntime() / 1000;
					kernelLog->logInfo(frames);
					frames = 0;
				}
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