#ifndef DIVISION_WINDOW_H
#define DIVISION_WINDOW_H

namespace Division
{
	class Window
	{
	public:
		virtual ~Window() {};
		virtual void* getWindowHandle() = 0;
		virtual void moveWindow(int X, int Y, int nWidth, int nHeight, bool rDraw) = 0;
	};
}
#endif
