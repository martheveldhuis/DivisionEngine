#include "Keyboard.h"

#include <dinput.h>
#include <iostream>

namespace Division
{
	Keyboard::Keyboard(HWND* windowHandle, IDirectInput8* directInput)
	{
		directInput_ = directInput;
		windowHandle_ = windowHandle; // TODO: does this one need to be set to NULL in destructor?

		initialize();
	}



	Keyboard::~Keyboard()
	{
		release();
	}



	void Keyboard::initialize()
	{
		if FAILED(directInput_->CreateDevice(GUID_SysKeyboard, &directInputKeyboard_, NULL)) {
			// log that this failed
			return;
		}

		if FAILED(directInputKeyboard_->SetDataFormat(&c_dfDIKeyboard))
		{
			// log that this failed
			release();
			return;
		}

		if FAILED(directInputKeyboard_->SetCooperativeLevel(*windowHandle_, DISCL_EXCLUSIVE | DISCL_FOREGROUND))
		{
			// log that this failed
			release();
			return;
		}

		if (FAILED(directInputKeyboard_->Acquire()))
		{
			// log that this failed
			return;
		}
	}


	void Keyboard::release()
	{
		directInput_ = NULL;

		if (directInputKeyboard_) {
			directInputKeyboard_->Release();
			directInputKeyboard_ = NULL;
		}
	}



	void Keyboard::getInput()
	{
		ZeroMemory(&keys_, sizeof(keys_));
		HRESULT stateResult = directInputKeyboard_->GetDeviceState(sizeof(keys_), (void*)keys_);

		if (FAILED(stateResult))
		{
			if (stateResult == DIERR_INPUTLOST || stateResult == DIERR_NOTACQUIRED)
				directInputKeyboard_->Acquire();
		}
	}



	void Keyboard::storeInputStates(InputStates* inputStates)
	{
		getInput();

		if (keys_[DIK_W] & 0x80)
			inputStates->moveForward = 1;

		if (keys_[DIK_A] & 0x80)
			inputStates->turnLeft = 1;

		if (keys_[DIK_S] & 0x80)
			inputStates->moveBackward = 1;

		if (keys_[DIK_D] & 0x80)
			inputStates->turnRight = 1;
	}
}