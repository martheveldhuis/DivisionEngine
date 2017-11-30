#include "WindowsInputManager.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Division
{
	WindowsInputManager::WindowsInputManager(HWND* windowHandle) : windowHandle_(windowHandle)
	{
		keyboard_ = NULL;
		mouse_ = NULL;

		initializeDirectInput();
		initializeInputDevices();
	}



	WindowsInputManager::~WindowsInputManager()
	{
		releaseDirectInput();
	}



	WindowsInputManager& WindowsInputManager::getInstance(HWND *windowHandle)
	{
		static WindowsInputManager instance(windowHandle);
		return instance;
	}



	// TODO: remove this to a general location for sharing
	void WindowsInputManager::initializeDirectInput()
	{
		HRESULT result = DirectInput8Create(GetModuleHandle(NULL), // TODO:  hisntance?
											DIRECTINPUT_VERSION,
											IID_IDirectInput8,
											(void**)&directInput_,
											NULL);
		if FAILED(result) {
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
					mouse_ = new Mouse(windowHandle_, directInput_);
					break;
			default:
				break;
			// TODO: log that input is not supported
		}

		return true;
	}



	void WindowsInputManager::initializeInputDevices()
	{
		HRESULT result = directInput_->EnumDevices(DI8DEVCLASS_ALL, enumDevicesCallback, 
												   this, DIEDFL_ATTACHEDONLY);
		if FAILED (result) {
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