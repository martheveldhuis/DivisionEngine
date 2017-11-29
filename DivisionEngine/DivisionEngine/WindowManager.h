#ifndef DIVISION_WINDOWMANAGER_H
#define DIVISION_WINDOWMANAGER_H

#include <list>

#include "Window.h"

namespace Division
{
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();
		Window* createWindow();
	private:
		std::list<Window*> windows_;
	};
}

#endif // !DIVISION_WINDOWMANAGER_H