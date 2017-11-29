#ifndef DIVISION_WINDOWSWINDOW_H
#define DIVISION_WINDOWSWINDOW_H

#include "Window.h"

#include <string>
#include <windows.h>
#include <windowsx.h>

class WindowsWindow : public Window
{
private:
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;
public:
	WindowsWindow();
	WindowsWindow(std::string);
	~WindowsWindow();
};
#endif
