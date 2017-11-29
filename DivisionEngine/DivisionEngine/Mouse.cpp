#include "Mouse.h"

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

		result = directInput_->CreateDevice(GUID_SysMouse, &directInputMouse_, NULL);
		if (FAILED(result)) {
			// log that this failed
			return;
		}

		result = directInputMouse_->SetDataFormat(&c_dfDIMouse);
		if FAILED(result)
		{
			// log that this failed
			return;
		}

		result = directInputMouse_->SetCooperativeLevel(*windowHandle_, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		if FAILED(result)
		{
			// log that this failed
			return;
		}

		DIPROPDWORD properties;
		properties.diph.dwSize = sizeof(DIPROPDWORD);
		properties.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		properties.diph.dwObj = 0;
		properties.diph.dwHow = DIPH_DEVICE;

		result = directInputMouse_->SetProperty(DIPROP_BUFFERSIZE, &properties.diph);
		if (FAILED(result))
		{
			// log that this failed
			return;
		}

		result = directInputMouse_->Acquire();
		if (FAILED(result))
		{
			// log that this failed
			return;
		}
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



	void Mouse::getInput()
	{
		DWORD bufferItemsToRead = 1;
		ZeroMemory(&buttonsAndAxes_, sizeof(buttonsAndAxes_));

		HRESULT res = directInputMouse_->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &buttonsAndAxes_, &bufferItemsToRead, 0);
		if (FAILED(res)) {
			if (res == DIERR_INPUTLOST || res == DIERR_NOTACQUIRED) {
				directInputMouse_->Acquire();
			}
		}
	}



	void Mouse::storeInputStates(InputStates* inputStates)
	{
		getInput();

		switch (buttonsAndAxes_.dwOfs) {
			case DIMOFS_X: {
				long xDelta = static_cast<long>(buttonsAndAxes_.dwData);
				if (xDelta > 0)
					inputStates->turnRight = xDelta;
				else {
					inputStates->turnLeft = xDelta;
				}
				break;
			}
				

			case DIMOFS_BUTTON0: {// left button
				long leftButton = static_cast<long>(buttonsAndAxes_.dwData);
				if (leftButton > 0)
					inputStates->action = true;
				break;
			}
		}
	}

}