#include "Mouse.h"
#include "LoggerPool.h"

namespace Division 
{
	Mouse::Mouse(HWND* windowHandle, IDirectInput8 * directInput) :
		directInput_(directInput), windowHandle_(windowHandle)
	{
		initialize();
	}



	Mouse::~Mouse()
	{
		release();
	}



	void Mouse::initialize()
	{
		HRESULT result;

		result = directInput_->CreateDevice(GUID_SysMouse, &directInputMouse_,
											NULL);
		if (FAILED(result)) {
			LoggerPool::getInstance()->getLogger("mouse")
				->logError("Couldn't create device, " + result);
			return;
		}

		result = directInputMouse_->SetDataFormat(&c_dfDIMouse);
		if FAILED(result)
		{
			LoggerPool::getInstance()->getLogger("mouse")
				->logError("Couldn't set data format, " + result);
			return;
		}

		result = directInputMouse_->SetCooperativeLevel(*windowHandle_, 
														DISCL_EXCLUSIVE | 
														DISCL_FOREGROUND);
		if FAILED(result)
		{
			LoggerPool::getInstance()->getLogger("mouse")
				->logError("Couldn't set coorperative level, " + result);
			return;
		}

		DIPROPDWORD properties;
		properties.diph.dwSize = sizeof(DIPROPDWORD);
		properties.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		properties.diph.dwObj = 0;
		properties.diph.dwHow = DIPH_DEVICE;

		result = directInputMouse_->SetProperty(DIPROP_BUFFERSIZE,
												&properties.diph);
		if (FAILED(result))
		{
			LoggerPool::getInstance()->getLogger("mouse")
				->logError("Couldn't set properties, " + result);
			return;
		}

		doAcquire();
	}



	void Mouse::release()
	{
		directInput_ = NULL;

		if (directInputMouse_) {
			directInputMouse_->Unacquire();
			directInputMouse_->Release();
			directInputMouse_ = NULL;
		}
	}



	void Mouse::doAcquire()
	{
		HRESULT result;

		for (int i = 0; i < 5; ++i) {

			result = directInputMouse_->Acquire();
			if (SUCCEEDED(result))
				return;
		}
	}



	void Mouse::getInput()
	{
		DWORD bufferItemsToRead = 1;
		ZeroMemory(&buttonsAndAxes_, sizeof(buttonsAndAxes_));

		HRESULT result;
		result = directInputMouse_->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
												  &buttonsAndAxes_,
												  &bufferItemsToRead, 0);
		if (FAILED(result)) {
			if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
				doAcquire();
		}
	}



	void Mouse::storeInputStates(InputStates* inputStates)
	{
		getInput();

		// TODO: check if this works(without converting to long, then also put in keyboard.
		DWORD deviceDataOffset = buttonsAndAxes_.dwOfs;

		switch (deviceDataOffset) {
			case DIMOFS_X: {
				if (deviceDataOffset > 0)
					inputStates->turnRight = deviceDataOffset;
				else {
					inputStates->turnLeft = deviceDataOffset;
				}
				break;
			}
				

			case DIMOFS_BUTTON0: {// left button
				if (deviceDataOffset > 0)
					inputStates->action = true;
				break;
			}
		}
	}

}