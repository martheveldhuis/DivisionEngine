#include "WindowsWindow.h"

WindowsWindow::WindowsWindow()
{
}

WindowsWindow::WindowsWindow(std::string str)
{
	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "Window";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		"WindowClass1",    // name of the window class
		"Our First Windowed Program",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		300,    // x-position of the window
		300,    // y-position of the window
		500,    // width of the window
		400,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		GetModuleHandle(NULL),    // application handle
		NULL);    // used with multiple windows, NULL

				  // display the window on the screen
	ShowWindow(hWnd, 0);
}

WindowsWindow::~WindowsWindow()
{
}