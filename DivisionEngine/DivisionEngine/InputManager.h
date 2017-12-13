#ifndef DIVISION_INPUTMANAGER_H
#define DIVISION_INPUTMANAGER_H

#include "InputDevice.h"

namespace Division
{
	class InputManager
	{
	public:
		virtual ~InputManager() {}
		virtual void setWindowHandle(void*) = 0;
		virtual InputStates getInput() = 0;
	};
}

#endif // !DIVISION_INPUTMANAGER_H
