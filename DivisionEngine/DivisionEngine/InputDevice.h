#ifndef DIVISION_INPUTDEVICE_H
#define DIVISION_INPUTDEVICE_H

namespace Division 
{
	/**
		Structure to store inputstates in.
	*/
	struct InputStates
	{
		bool moveForward;	/**< W key */
		bool moveBackward;	/**< S key */
		bool moveLeft;		/**< A key */
		bool moveRight;		/**< D key */
		bool moveUp;		/**< Left mouse button */
		bool moveDown;		/**< Right mouse button */
		long turnLeft;		/**< Moving the mouse to the left */
		long turnRight;		/**< Moving the mouse to the left */
		long turnUp;		/**< Moving the mouse up */
		long turnDown;		/**< Moving the mouse down */
	};

	/**
		Interface that defines an input device.
	*/
	class InputDevice
	{
	public:
		virtual ~InputDevice() {};
		/**
			Initializes the device so it can be used.
		*/
		virtual void initialize() = 0;
		/**
			Free up any objects. Used when destructing.
		*/
		virtual void release() = 0;
		/**
			Acquire the device from the OS multiple times.
		*/
		virtual void doAcquire() = 0;
		/**
			Get input from the device, set it on its own container.
		*/
		virtual void getInput() = 0;
		/**
			Store input from the device in the input states struct, converting
			the input stored to the values of the input states struct.
			@param inputStates The struct in which the input will be stored.
		*/
		virtual void storeInputStates(InputStates* inputStates) = 0;
	};
}

#endif // !DIVISION_INPUTDEVICE_H