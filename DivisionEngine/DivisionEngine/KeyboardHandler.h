#ifndef DIVISION_KEYBOARDHANDLER_H
#define DIVISION_KEYBOARDHANDLER_H

#include "InputHandler.h"

namespace Division
{
	/**
		Handles input taken from the keyboard.
	*/
	class KeyboardHandler : public InputHandler
	{
	public:
		KeyboardHandler();
		virtual ~KeyboardHandler();
		virtual void handleInput(const unsigned int inputMask);
	};
}

#endif // !DIVISION_KEYBOARDHANDLER_H


