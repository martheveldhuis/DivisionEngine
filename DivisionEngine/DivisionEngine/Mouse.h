#ifndef DIVISION_MOUSE_H
#define DIVISION_MOUSE_H

#include <dinput.h>

#include "InputDevice.h"

namespace Division
{
	class Mouse : public InputDevice
	{
	public:
		Mouse(HWND*, IDirectInput8*);
		virtual ~Mouse();
		virtual void initialize();
		virtual void release();
		virtual void getInput();
		virtual void storeInputStates(InputStates*);
	private:
		HWND* windowHandle_;
		IDirectInput8* directInput_;
		IDirectInputDevice8* directInputMouse_;
		DIDEVICEOBJECTDATA buttonsAndAxes_;
		//DIMOUSESTATE state_; not necessary for buffered data
	};
}

#endif // !DIVISION_MOUSE_H
