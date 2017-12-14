#ifndef DIVISION_KEYBOARD_H
#define DIVISION_KEYBOARD_H

#include <dinput.h>

#include "InputDevice.h"

namespace Division
{
	class Keyboard : public InputDevice
	{
	public:
		Keyboard(HWND*, IDirectInput8*);
		virtual ~Keyboard();
		virtual void initialize();
		virtual void release();
		virtual void doAcquire();
		virtual void getInput();
		virtual void storeInputStates(InputStates*);
	private:
		HWND* windowHandle_;
		IDirectInput8* directInput_;
		IDirectInputDevice8* directInputKeyboard_;
		BYTE keys_[256];
	};
}

#endif // !DIVISION_KEYBOARD_H


