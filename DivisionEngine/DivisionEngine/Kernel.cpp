#include "Kernel.h"
#include <map>

#include "Clock.h"
#include "LoggerPool.h"

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

		Scene* scene = sceneManager_->loadScene("tst");

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
					lastSec = (int) clock.getRuntime() / 1000;
					kernelLog->logInfo(frames);
					frames = 0;
				}
				scene->render();
			}

		}
	}
}