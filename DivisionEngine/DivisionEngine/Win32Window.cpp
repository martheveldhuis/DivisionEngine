#include "Win32Window.h"
namespace Division
{
	Win32Window::Win32Window(std::string winTitle, int X, int Y, int nWidth, int nHeight, DWORD style) :
		x_(X) , y_(Y), 
		nWidth_(nWidth), nHeight_(nHeight)
	{
		//Create a window class.
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, Win32Window::WindowProc, 0L, 0L,
			GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			"window", NULL };

		//Register the window class.
		RegisterClassEx(&wc);

		//Create the application's window.
		windowHandle_ = CreateWindow("window", winTitle.c_str(),
			style, x_, y_, nWidth_, nHeight_,
			NULL, NULL, wc.hInstance, NULL);

		ShowWindow(windowHandle_, SW_SHOWDEFAULT);
	}



	Win32Window::~Win32Window()
	{
	}
	


	LRESULT WINAPI Win32Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}



	void* Win32Window::getWindowHandle()
	{
		return windowHandle_;
	}



	void Win32Window::moveWindow(int X, int Y, bool rDraw)
	{
		x_ = X;
		y_ = Y;
		MoveWindow(windowHandle_, x_, y_, nWidth_, nHeight_, rDraw);

	}



	void Win32Window::resizeWindow(int nWidth, int nHeight, bool rDraw)
	{
		nWidth_ = nWidth;
		nHeight_ = nHeight;
		MoveWindow(windowHandle_, x_, y_, nWidth_, nHeight_, rDraw);
	}

}