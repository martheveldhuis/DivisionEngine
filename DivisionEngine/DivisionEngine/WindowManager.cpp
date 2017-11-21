#include "WindowManager.h"

namespace Division
{
	WindowManager::WindowManager()
	{
	}

	WindowManager::~WindowManager()
	{
		// TODO: delete the list
	}
	Window* WindowManager::createWindow()
	{
		Window *createdWindow = new Window();
		windows_.push_back(createdWindow);
		return createdWindow;
	}
}