#ifndef DIVISION_INPUTHANDLER_H
#define DIVISION_INPUTHANDLER_H

namespace Division 
{
	/**
		Interface for different kinds of input handlers. 
		Provides a method to handle the input of the device, such as a mouse.
	*/
	class InputHandler
	{
	public:
		virtual ~InputHandler() = 0;
		virtual void handleInput(const unsigned int inputMask) = 0;
	};
}

#endif // !DIVISION_INPUTHANDLER_H