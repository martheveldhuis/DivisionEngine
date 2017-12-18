#ifndef DIVISION_WINDOWSINPUTMANAGER_H
#define DIVISION_WINDOWSINPUTMANAGER_H

#include <Windows.h>
#include <dinput.h>

#include "InputManager.h"

namespace Division
{
	/**
		Direct input implementation for the input manager interface.
	*/
	class DirectInputManager : public InputManager
	{
	public:
		DirectInputManager();
		~DirectInputManager();
		void setWindowHandle(void*);
		InputStates getInput();
		/**
			Callback that is called each time a device is found when
			enumerating devices in initializeInputDevices. Calls enumDevices
			with this class' context so we can use the class' members.
			@param device The current enumerated device structure.
			@param context The contents of this class.
			@returns Whether the enumeration should stop or continue.
		*/
		static BOOL CALLBACK enumDevicesCallback(LPCDIDEVICEINSTANCE device,
												 LPVOID context);
	private:
		/**
			Creates the direct input interface.
		*/
		void initializeDirectInput();
		/**
			Enumerates over the attached input devices. Calls
			enumDevicesCallback for each device found.
		*/
		void initializeInputDevices();
		/**
			Determines the device's type. Creates a direct input keyboard or a
			direct input mouse object.
			@param device The current enumerated device structure.
			@returns Whether the enumeration should stop or continue.
		*/
		BOOL enumDevices(LPCDIDEVICEINSTANCE device);
		HWND windowHandle_ = NULL;
		IDirectInput8* directInput_ = NULL;
		InputDevice* keyboard_ = NULL;
		InputDevice* mouse_ = NULL;
	};
}

#endif // !DIVISION_WINDOWSINPUTMANAGER_H

