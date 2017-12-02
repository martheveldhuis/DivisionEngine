#include "Win32Window.h"
namespace Division {

	Win32Window::Win32Window(std::string winName = "x", std::string winTitle = "x")
	{
		//Create a window class.
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, Win32Window::MsgProc, 0L, 0L,
			GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			winName.c_str(), NULL };

		//Register the window class.
		RegisterClassEx(&wc);

		//Create the application's window.
		windowHandle_ = CreateWindow(winName.c_str(), winTitle.c_str(),
			WS_OVERLAPPEDWINDOW, 100, 100, 256, 256,
			NULL, NULL, wc.hInstance, NULL);

		ShowWindow(windowHandle_, SW_SHOWDEFAULT);
	}

	Win32Window::~Win32Window()
	{
	}

	//Besides the main function, there must be a message processing function
	LRESULT WINAPI Win32Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	HWND Win32Window::getWindowHandle()
	{
		return windowHandle_;
	}
}