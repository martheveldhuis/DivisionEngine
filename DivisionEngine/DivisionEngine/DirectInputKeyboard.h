#ifndef DIVISION_DIRECTINPUTKEYBOARD_H
#define DIVISION_DIRECTINPUTKEYBOARD_H

#include <dinput.h>

#include "InputDevice.h"

namespace Division
{
	/**
		Class for a direct input keyboard.
	*/
	class DirectInputKeyboard : public InputDevice
	{
	public:
		/**
			@param windowHandle The window on which the keyboard is captured.
			@param directInput Direct input interface, to create the device.
		*/
		DirectInputKeyboard(HWND windowHandle, IDirectInput8* directInput);
		virtual ~DirectInputKeyboard();
		virtual void initialize();
		virtual void release();
		virtual void doAcquire();
		virtual void getInput();
		virtual void storeInputStates(InputStates*);
	private:
		HWND windowHandle_;
		IDirectInput8* directInput_;
		IDirectInputDevice8* directInputKeyboard_;
		BYTE keys_[256]; /**< Container for storing the state of each key. */
	};
}

#endif // !DIVISION_DIRECTINPUTKEYBOARD_H


