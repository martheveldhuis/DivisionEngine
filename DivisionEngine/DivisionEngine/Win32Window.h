#ifndef DIVISION_WINDOWSWINDOW_H
#define DIVISION_WINDOWSWINDOW_H

#include "Window.h"

#include <Windows.h>
#include <string>

namespace Division
{
	/**
		Class for the creation and manipulation of a Win32 window.
	*/
	class Win32Window : public Window
	{
	public:
		/**
			Create a win32 window
			@param winTitle The title the window will show to windows.
			@param X Set initial x location of the window.
			@param Y Set initial y location of the window.
			@param nWidth Set initial width of the window.
			@param nHeight Set initial height of the window.
			@param style Set the Style for the window. See https://msdn.microsoft.com/en-us/library/windows/desktop/ms632600(v=vs.85).aspx.
		*/
		Win32Window(std::string winTitle = "x", int X = 100, int Y = 100, int nWidth = 600, int nHeight = 600, DWORD style = WS_BORDER);
		~Win32Window();
		/**
			An application-defined function that processes messages sent to a window. 
			@param hwnd A handle to the window.
			@param uMsg The message.	See https://msdn.microsoft.com/en-us/library/windows/desktop/ms644927(v=vs.85).aspx#system_defined.
			@param wParam Additional message information. 
			@param lParam Additional message information. 
			@returns LRESULT The return value is the result of the message processing and depends on the message sent.
		
		*/
		static LRESULT WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
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