#include "WindowsInputManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "LoggerPool.h"

namespace Division
{
	WindowsInputManager::WindowsInputManager()
	{
		initializeDirectInput();
	}



	WindowsInputManager::~WindowsInputManager()
	{
		if (directInput_) {
			directInput_->Release();
			directInput_ = NULL;
		}

		if (keyboard_) {
			delete keyboard_;
			keyboard_ = NULL;
		}

		if (mouse_) {
			delete mouse_;
			mouse_ = NULL;
		}
	}



	void WindowsInputManager::setWindowHandle(void* windowHandle)
	{
		windowHandle_ = static_cast<HWND>(windowHandle);
		initializeInputDevices();
	}




	void WindowsInputManager::initializeDirectInput()
	{
		HRESULT result = DirectInput8Create(GetModuleHandle(NULL),
											DIRECTINPUT_VERSION,
											IID_IDirectInput8,
											(void**)&directInput_,
											NULL);
		if FAILED(result) {
			LoggerPool::getInstance()->getLogger("windowsInputManager")
				->logError("Failed to create Direct Input, " + result);
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
					keyboard_ = new Keyboard(&windowHandle_, directInput_);
					break;
			case DI8DEVTYPE_MOUSE:
				if (!mouse_)
					mouse_ = new Mouse(&windowHandle_, directInput_);
					break;
			default:
				LoggerPool::getInstance()->getLogger("windowsInputManager")
					->logInfo("The device type is not supported, " 
							  + (device->dwDevType & 0x000000ff));
				break;
		}

		return true;
	}



	void WindowsInputManager::initializeInputDevices()
	{
		HRESULT result = directInput_->EnumDevices(DI8DEVCLASS_ALL, enumDevicesCallback, 
												   this, DIEDFL_ATTACHEDONLY);
		if FAILED (result) {
			LoggerPool::getInstance()->getLogger("windowsInputManager")
				->logError("Failed to enumerate devices, " + result);
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