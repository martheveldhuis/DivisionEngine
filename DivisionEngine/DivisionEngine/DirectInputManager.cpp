#include "DirectInputManager.h"
#include "DirectInputKeyboard.h"
#include "DirectInputMouse.h"
#include "LoggerPool.h"

namespace Division
{
	DirectInputManager::DirectInputManager()
	{
		initializeDirectInput();
	}



	DirectInputManager::~DirectInputManager()
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



	void DirectInputManager::setWindowHandle(void* windowHandle)
	{
		windowHandle_ = static_cast<HWND>(windowHandle);
		keyboard_ = NULL;
		mouse_ = NULL;
		initializeInputDevices();
	}

	void * DirectInputManager::getWindowHandle()
	{
		return windowHandle_;
	}




	void DirectInputManager::initializeDirectInput()
	{
		HRESULT result = DirectInput8Create(GetModuleHandle(NULL),
											DIRECTINPUT_VERSION,
											IID_IDirectInput8,
											(void**)&directInput_,
											NULL);
		if FAILED(result) {
			LoggerPool::getInstance()->getLogger("windowsInputManager")
				->logError("Failed to create Direct Input");
		}
	}



	BOOL DirectInputManager::enumDevicesCallback(LPCDIDEVICEINSTANCE device,
												 LPVOID context)
	{
		// Necessary to be able to use our class' members without 'static'.
		DirectInputManager* thisContext;
		thisContext = static_cast<DirectInputManager*>(context);
		return thisContext->enumDevices(device);
	}



	BOOL DirectInputManager::enumDevices(LPCDIDEVICEINSTANCE device)
	{
		switch (device->dwDevType & 0x000000ff) {
			case DI8DEVTYPE_KEYBOARD:
				if (!keyboard_)
					keyboard_ = new DirectInputKeyboard(windowHandle_, 
														directInput_);
					break;
			case DI8DEVTYPE_MOUSE:
				if (!mouse_)
					mouse_ = new DirectInputMouse(windowHandle_, directInput_);
					break;
			default:
				// The device type is not supported.
				break;
		}

		return true;
	}



	void DirectInputManager::initializeInputDevices()
	{
		HRESULT result = directInput_->EnumDevices(DI8DEVCLASS_ALL,
												   enumDevicesCallback, 
												   this, DIEDFL_ATTACHEDONLY);
		if FAILED (result) {
			LoggerPool::getInstance()->getLogger("windowsInputManager")
				->logError("Failed to enumerate devices");
		}

	}

	
	InputStates DirectInputManager::getInput()
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