#ifndef DIVISION_WINDOW_H
#define DIVISION_WINDOW_H

namespace Division
{
	class Window
	{
	public:
		virtual ~Window() = 0;
		virtual void* getWindowHandle() = 0;
	};
}
#endif
