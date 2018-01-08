#include "DirectInputMouse.h"
#include "LoggerPool.h"

namespace Division 
{
	DirectInputMouse::DirectInputMouse(HWND windowHandle, IDirectInput8 * directInput) :
		directInput_(directInput), windowHandle_(windowHandle)
	{
		initialize();
	}



	DirectInputMouse::~DirectInputMouse()
	{
		release();
	}



	void DirectInputMouse::initialize()
	{
		HRESULT result;

		result = directInput_->CreateDevice(GUID_SysMouse, &directInputMouse_,
											NULL);
		if (FAILED(result)) {
			LoggerPool::getInstance()->getLogger("mouse")
				->logError("Couldn't create device");
			return;
		}

		result = directInputMouse_->SetDataFormat(&c_dfDIMouse);
		if FAILED(result) {
			LoggerPool::getInstance()->getLogger("mouse")
				->logError("Couldn't set data format");
			return;
		}

		result = directInputMouse_->SetCooperativeLevel(windowHandle_, 
														DISCL_EXCLUSIVE | 
														DISCL_FOREGROUND);
		if FAILED(result) {
			LoggerPool::getInstance()->getLogger("mouse")
				->logError("Couldn't set coorperative level");
			return;
		}

		DIPROPDWORD properties;
		properties.diph.dwSize = sizeof(DIPROPDWORD);
		properties.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		properties.diph.dwObj = 0;
		properties.diph.dwHow = DIPH_DEVICE;

		result = directInputMouse_->SetProperty(DIPROP_BUFFERSIZE,
												&properties.diph);
		if (FAILED(result)) {
			LoggerPool::getInstance()->getLogger("mouse")
				->logError("Couldn't set properties");
			return;
		}

		doAcquire();
	}



	void DirectInputMouse::release()
	{
		directInput_ = NULL;

		if (directInputMouse_) {
			directInputMouse_->Unacquire();
			directInputMouse_->Release();
			directInputMouse_ = NULL;
		}
	}



	void DirectInputMouse::doAcquire()
	{
		// Wait our turn (after higher prio programs) to gain access.
		for (int i = 0; i < 5; ++i) {
			if (SUCCEEDED(directInputMouse_->Acquire()))
				return;
		}
	}



	void DirectInputMouse::getInput()
	{
		bufferItemsToRead_ = INFINITE;
		ZeroMemory(&buttonsAndAxes_, sizeof(buttonsAndAxes_));

		HRESULT result;

		// Peek to check the amount of buffer items to read, put in variable.
		result = directInputMouse_->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
												  NULL, &bufferItemsToRead_,
												  DIGDD_PEEK);
		if (FAILED(result)) {
			// In these cases, new acquires are useful.
			if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
				doAcquire();
			// If it fails, do not read any items.
			bufferItemsToRead_ = 0;
		}
		else {
			buttonsAndAxes_ = new DIDEVICEOBJECTDATA[bufferItemsToRead_];
			result = directInputMouse_->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
													  buttonsAndAxes_,
													  &bufferItemsToRead_, 0);
		}
	}



	void DirectInputMouse::storeInputStates(InputStates* inputStates)
	{
		getInput();

		for (int i = 0; i < bufferItemsToRead_; ++i) {
			switch (buttonsAndAxes_[i].dwOfs) {
				// Slide mouse left / right.
				case DIMOFS_X: {
					long xDelta = static_cast<long>(buttonsAndAxes_[i].dwData);
					if (xDelta > 0)
						inputStates->turnRight += xDelta;
					else {
						inputStates->turnLeft += -(xDelta);
					}
					break;
				}
				// Slide mouse up / down.
				case DIMOFS_Y : {
					long yDelta = static_cast<long>(buttonsAndAxes_[i].dwData);
					if (yDelta > 0)
						inputStates->turnDown += yDelta;
					else {
						inputStates->turnUp += -(yDelta);
					}
					break;
				}
				// Left mouse button.
				case DIMOFS_BUTTON0: {
					long leftButton = static_cast<long>(buttonsAndAxes_[i].dwData);
					if (leftButton > 0)
						// Fill input states with a corresponding action.
					break;
				}
				// Right mouse button.
				case DIMOFS_BUTTON1: {
					long rightButton = static_cast<long>(buttonsAndAxes_[i].dwData);
					if (rightButton > 0)
						// Fill input states with a corresponding action.
					break;
				}
			}
		}
	}
}