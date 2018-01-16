#include "Win32Window.h"
namespace Division
{
	Win32Window::Win32Window(std::string winTitle = "x")
	{
		//Create a window class.
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, Win32Window::MsgProc, 0L, 0L,
			GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			"window", NULL };

		//Register the window class.
		RegisterClassEx(&wc);

		//Create the application's window.
		windowHandle_ = CreateWindow("window", winTitle.c_str(),
			WS_BORDER, 100, 100, 800, 600,
			NULL, NULL, wc.hInstance, NULL);

		ShowWindow(windowHandle_, SW_SHOWDEFAULT);
	}
	Win32Window::Win32Window(int X, int Y, int nWidth, int nHeight, std::string winTitle = "x" , DWORD style = WS_BORDER)
	{
		//Create a window class.
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, Win32Window::MsgProc, 0L, 0L,
			GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			"window", NULL };

		//Register the window class.
		RegisterClassEx(&wc);

		//Create the application's window.
		windowHandle_ = CreateWindow("window", winTitle.c_str(),
			style, X, Y, nWidth, nHeight,
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

	void* Win32Window::getWindowHandle()
	{
		return windowHandle_;
	}
	void Win32Window::moveWindow(int X, int Y, int nWidth, int nHeight, bool rDraw)
	{
		MoveWindow(windowHandle_, X, Y, nWidth, nHeight, rDraw);
	}
}