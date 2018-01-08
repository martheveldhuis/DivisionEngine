#include "DirectInputKeyboard.h"
#include "LoggerPool.h"

namespace Division
{
	DirectInputKeyboard::DirectInputKeyboard(HWND windowHandle, 
											 IDirectInput8* directInput) :
		directInput_(directInput), windowHandle_(windowHandle)
	{
		initialize();
	}



	DirectInputKeyboard::~DirectInputKeyboard()
	{
		release();
	}



	void DirectInputKeyboard::initialize()
	{
		HRESULT result;

		result = directInput_->CreateDevice(GUID_SysKeyboard, 
											&directInputKeyboard_,
											NULL);
		if FAILED(result) {
			LoggerPool::getInstance()->getLogger("keyboard")
				->logError("Couldn't create device");
			return;
		}

		result = directInputKeyboard_->SetDataFormat(&c_dfDIKeyboard);
		if FAILED(result) {
			LoggerPool::getInstance()->getLogger("keyboard")
				->logError("Couldn't set data format");
			release();
			return;
		}

		result = directInputKeyboard_->SetCooperativeLevel(windowHandle_, 
															DISCL_EXCLUSIVE | 
															DISCL_FOREGROUND);
		if FAILED(result) {
			LoggerPool::getInstance()->getLogger("keyboard")
				->logError("Couldn't set coorperative level");
			release();
			return;
		}

		doAcquire();
	}



	void DirectInputKeyboard::release()
	{
		directInput_ = NULL;

		if (directInputKeyboard_) {
			directInputKeyboard_->Unacquire();
			directInputKeyboard_->Release();
			directInputKeyboard_ = NULL;
		}
	}



	void DirectInputKeyboard::doAcquire()
	{
		// Wait our turn (after higher prio programs) to gain access.
		for (int i = 0; i < 5; ++i) {
			if (SUCCEEDED(directInputKeyboard_->Acquire()))
				return;
		}
	}



	void DirectInputKeyboard::getInput()
	{
		ZeroMemory(&keys_, sizeof(keys_));

		HRESULT result = directInputKeyboard_->GetDeviceState(sizeof(keys_), 
															  (void*)keys_);
		if (FAILED(result)) {
			// In these cases, new acquires are useful.
			if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
				doAcquire();
		}
	}



	void DirectInputKeyboard::storeInputStates(InputStates* inputStates)
	{
		getInput();

		if (keys_[DIK_W] & 0x80)
			inputStates->moveForward = true;

		if (keys_[DIK_A] & 0x80)
			inputStates->moveLeft = true;

		if (keys_[DIK_S] & 0x80)
			inputStates->moveBackward = true;

		if (keys_[DIK_D] & 0x80)
			inputStates->moveRight = true;

		if (keys_[DIK_SPACE] & 0x80)
			inputStates->moveUp = true;

		if (keys_[DIK_X] & 0x80)
			inputStates->moveDown = true;
	}
}