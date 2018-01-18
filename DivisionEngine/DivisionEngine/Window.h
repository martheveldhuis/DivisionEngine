#ifndef DIVISION_WINDOW_H
#define DIVISION_WINDOW_H

namespace Division
{
	/**
		Interface that defines an window.
	*/
	class Window
	{
	public:
		virtual ~Window() {};
		/**
			Get the window handle from the window
			@returns void pointer window handle
		*/
		virtual void* getWindowHandle() = 0;
		/**
			Move this window to the desired location in pixels.
			@param X The x coordinates for the desired location.
			@param Y The y coordinates for the desired location.
			@param rDraw Option to force redraw the window. 
		*/
		virtual void moveWindow(int X, int Y, bool rDraw) = 0;
		/**
			Resize this window to the desired size in pixels.
			@param nWidth The length for the desired width.
			@param nHeight The length for the desired Height.
			@param rDraw Option to force redraw the window.
		*/
		virtual void resizeWindow(int nWidth, int nHeight, bool rDraw) = 0;
	};
}
#endif
