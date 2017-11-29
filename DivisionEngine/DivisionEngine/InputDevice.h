#ifndef DIVISION_INPUTDEVICE_H
#define DIVISION_INPUTDEVICE_H

namespace Division 
{
	struct InputStates
	{
		bool moveForward;	// w
		bool moveBackward;	// s
		bool moveLeft;		// a
		bool moveRight;		// d
		long turnLeft;		// ml
		long turnRight;		// mr
		bool action;		// lmb
	};

	class InputDevice
	{
	public:
		virtual ~InputDevice() = 0 {};
		virtual void initialize() = 0;
		virtual void release() = 0;
		virtual void storeInputStates(InputStates*) = 0;
	};
}

#endif // !DIVISION_INPUTDEVICE_H