#include "WindowsInputManager.h"
#include "Keyboard.h"

namespace Division
{
	WindowsInputManager::WindowsInputManager(HWND* windowHandle)
	{
		windowHandle_ = windowHandle;

		keyboard_ = NULL;
		mouse_ = NULL;
		//TODO: this should only be called once, create singleton?
		initializeDirectInput();
		initializeInputDevices();
	}



	WindowsInputManager::~WindowsInputManager()
	{
		releaseDirectInput();
	}



	void WindowsInputManager::initializeDirectInput()
	{
		if FAILED(DirectInput8Create(GetModuleHandle(NULL), // TODO:  hisntance?
									 DIRECTINPUT_VERSION,
									 IID_IDirectInput8,
									 (void**)&directInput_,
									 NULL))
		{
			// TODO: log that this failed
		}
	}



	void WindowsInputManager::releaseDirectInput()
	{
		if (directInput_) {
			directInput_->Release();
			directInput_ = NULL;
		}
	}




	BOOL WindowsInputManager::enumDevicesCallback(LPCDIDEVICEINSTANCE device, LPVOID context)
	{
		// necessary to be able to use our class' members without 'static'
		WindowsInputManager* thisContext = static_cast<WindowsInputManager*>(context);
		return thisContext->enumDevices(device);
	}



	BOOL WindowsInputManager::enumDevices(LPCDIDEVICEINSTANCE device)
	{
		switch (device->dwDevType & 0x000000ff) {
			case DI8DEVTYPE_KEYBOARD:
				if (!keyboard_)
					keyboard_ = new Keyboard(windowHandle_, directInput_);
					break;
			case DI8DEVTYPE_MOUSE:
				if (!mouse_)
				// TODO: create a mouse
					break;
			default:
				break;
			// TODO: log that input is not supported
		}

		return true;
	}



	void WindowsInputManager::initializeInputDevices()
	{
		if FAILED (directInput_->EnumDevices(DI8DEVCLASS_ALL, enumDevicesCallback, this, DIEDFL_ATTACHEDONLY)) {
			// TODO: log that this failed
		}

	}

	
	InputStates WindowsInputManager::getInput()
	{
		InputStates inputStates;
		ZeroMemory(&inputStates, sizeof(InputStates));

		if (keyboard_) {
			keyboard_->storeInputStates(&inputStates);
		}

		if (mouse_) {
			mouse_->storeInputStates(&inputStates);
		}

		return inputStates;
	}
}