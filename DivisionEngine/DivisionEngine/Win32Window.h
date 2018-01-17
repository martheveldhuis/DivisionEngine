#ifndef DIVISION_WINDOWSWINDOW_H
#define DIVISION_WINDOWSWINDOW_H

#include "Window.h"

#include <Windows.h>
#include <string>

// define the screen resolution
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080
namespace Division
{
	class Win32Window : public Window
	{
	public:
		Win32Window(std::string winTitle = "x");
		Win32Window(int X, int Y, int nWidth, int nHeight, std::string winTitle = "x", DWORD style = WS_BORDER);
		~Win32Window();
		static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void* getWindowHandle();
		void moveWindow(int X, int Y, bool rDraw);
		void resizeWindow(int nWidth, int nHeight, bool rDraw);

	private:
		HWND windowHandle_;
		int x_;
		int y_;
		int nWidth_;
		int nHeight_;
	};
}

#endif // !DIVISION_WINDOWSWINDOW_H