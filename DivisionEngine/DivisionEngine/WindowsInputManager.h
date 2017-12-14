#ifndef DIVISION_WINDOWSINPUTMANAGER_H
#define DIVISION_WINDOWSINPUTMANAGER_H

#include <Windows.h>
#include <dinput.h>

#include "InputDevice.h"
#include "InputManager.h"

namespace Division
{
	class WindowsInputManager : public InputManager
	{
	public:
		WindowsInputManager();
		~WindowsInputManager();
		void setWindowHandle(void*);
		InputStates getInput();
		static BOOL CALLBACK enumDevicesCallback(LPCDIDEVICEINSTANCE, LPVOID);
	private:
		void initializeDirectInput();
		void initializeInputDevices();
		BOOL enumDevices(LPCDIDEVICEINSTANCE);
		HWND windowHandle_ = NULL;
		IDirectInput8* directInput_ = NULL;
		InputDevice* keyboard_ = NULL;
		InputDevice* mouse_ = NULL;
	};
}

#endif // !DIVISION_WINDOWSINPUTMANAGER_H

