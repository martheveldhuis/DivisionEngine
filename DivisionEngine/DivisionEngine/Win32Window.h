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
	class Win32Window : public virtual Window
	{
	public:
		Win32Window(std::string, std::string);
		~Win32Window();
		static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		HWND getWindowHandle();
	private:
		HWND windowHandle_;
	};
}

#endif // !DIVISION_WINDOWSWINDOW_H