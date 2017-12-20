#ifndef DIVISION_INPUTMANAGER_H
#define DIVISION_INPUTMANAGER_H

#include "InputDevice.h"

namespace Division
{
	/**
		Interface for any type of input manager that is able to retrieve input
		from input devices on a window, and store those in the input states
		struct.
	*/
	class InputManager
	{
	public:
		virtual ~InputManager() {}
		/**
			Sets the window handle on which to handle the input.
			@param windowHandle void pointer to any type of window handle.
		*/
		virtual void setWindowHandle(void* windowHandle) = 0;
		/**
			Retrieves the windowhandle from which to handle input
			@returns void pointer windowhandle		
		*/
		virtual void* getWindowHandle() = 0;
		/**
			Retrieves the input data from the input devices.
			@returns A struct filled with the set input data.
		*/
		virtual InputStates getInput() = 0;
	};
}

#endif // !DIVISION_INPUTMANAGER_H
