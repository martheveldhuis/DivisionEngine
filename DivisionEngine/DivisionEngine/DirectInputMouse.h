#ifndef DIVISION_DIRECTINPUTMOUSE_H
#define DIVISION_DIRECTINPUTMOUSE_H

#include <dinput.h>

#include "InputDevice.h"

namespace Division
{
	/**
		Class for a direct input mouse.
	*/
	class DirectInputMouse : public InputDevice
	{
	public:
		/**
			@param windowHandle The window on which the mouse is captured.
			@param directInput Direct input interface, to create the device.
		*/
		DirectInputMouse(HWND, IDirectInput8*);
		virtual ~DirectInputMouse();
		virtual void initialize();
		virtual void release();
		virtual void doAcquire();
		virtual void getInput();
		virtual void storeInputStates(InputStates*);
	private:
		HWND windowHandle_;
		IDirectInput8* directInput_;
		IDirectInputDevice8* directInputMouse_;
		DIDEVICEOBJECTDATA* buttonsAndAxes_; /**< Stores mouse clicks & moves*/
		DWORD bufferItemsToRead_;
	};
}

#endif // !DIVISION_DIRECTINPUTMOUSE_H
