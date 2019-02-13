#include "XBoxController.h"
constexpr double LEFT_STICK_DEADZONE = 8000.0;

bool GamePadXbox::is_connected()
{
	_controllerNum = player_ - 1;

	memset(&_controllerState, 0, sizeof(XINPUT_STATE));

	DWORD Result;

	Result = XInputGetState(_controllerNum, &_controllerState);

	if (Result == ERROR_SUCCESS)	return true;
	else return false;
}

void GamePadXbox::vibrate(float leftmotor, float rightmotor)
{
	XINPUT_VIBRATION Vibration;

	memset(&Vibration, 0, sizeof(XINPUT_VIBRATION));

	int leftVib = (int)(leftmotor*65535.0f);
	int rightVib = (int)(rightmotor*65535.0f);

	Vibration.wLeftMotorSpeed = leftVib;
	Vibration.wRightMotorSpeed = rightVib;

	XInputSetState((int)_controllerNum, &Vibration);
}

void GamePadXbox::update()
{
	OldState = State;

	State.reset();

	if (_controllerState.Gamepad.bRightTrigger && _controllerState.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		State._right_trigger = _controllerState.Gamepad.bRightTrigger / 255.0f;
	}

	if (_controllerState.Gamepad.bLeftTrigger && _controllerState.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		State._left_trigger = _controllerState.Gamepad.bLeftTrigger / 255.0f;
	}

	// Get the Buttons
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) State._buttons[GamePad_Button_DPAD_UP] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) State._buttons[GamePad_Button_DPAD_DOWN] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) State._buttons[GamePad_Button_DPAD_LEFT] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) State._buttons[GamePad_Button_DPAD_RIGHT] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_START) State._buttons[GamePad_Button_START] = true;
	if (_controllerState.Gamepad.wButtons &XINPUT_GAMEPAD_BACK) State._buttons[GamePad_Button_BACK] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) State._buttons[GamePad_Button_LEFT_THUMB] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) State._buttons[GamePad_Button_RIGHT_THUMB] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) State._buttons[GamePad_Button_LEFT_SHOULDER] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) State._buttons[GamePad_Button_RIGHT_SHOULDER] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A) State._buttons[GamePad_Button_A] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B) State._buttons[GamePad_Button_B] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X) State._buttons[GamePad_Button_X] = true;
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) State._buttons[GamePad_Button_Y] = true;

	if ((_controllerState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		_controllerState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(_controllerState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			_controllerState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		_controllerState.Gamepad.sThumbLX = 0;
		_controllerState.Gamepad.sThumbLY = 0;
	}

	float leftThumbY = _controllerState.Gamepad.sThumbLY;
	if (leftThumbY)
	{
		State._left_thumbstick.y = leftThumbY / 32767;
	}

	float leftThumbX = _controllerState.Gamepad.sThumbLX;
	if (leftThumbX)
	{
		State._left_thumbstick.x = leftThumbX / 32767;
	}

	//1.0　もしいくは -1.0と比較するようにしてしまうと上下左右しか判定されなくなる
	//斜めにも対応させるには0.5もしくは-0.5と比較するべき

	if (State._left_thumbstick.x <= -0.5f)
	{
		State._left_controllflag.left = true;
	}
	if (State._left_thumbstick.x >= 0.5f)
	{
		State._left_controllflag.right = true;
	}
	if (State._left_thumbstick.y <= -0.5f)
	{
		State._left_controllflag.down = true;
	}
	if (State._left_thumbstick.y >= 0.5f)
	{
		State._left_controllflag.up = true;
	}
	if ((_controllerState.Gamepad.sThumbRX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		_controllerState.Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(_controllerState.Gamepad.sThumbRY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			_controllerState.Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		_controllerState.Gamepad.sThumbRX = 0;
		_controllerState.Gamepad.sThumbRY = 0;
	}

	float rightThumbY = _controllerState.Gamepad.sThumbRY;

	if (rightThumbY)
	{
		State._right_thumbstick.y = rightThumbY / 32767;
	}

	float rightThumbX = _controllerState.Gamepad.sThumbRX;

	if (rightThumbX)
	{
		State._right_thumbstick.x = rightThumbX / 32767;
	}
}

GamePadState GamePadXbox::GetState()
{
	return State;
}

bool GamePadXbox::GetLeftControllerTrigger(int flag)
{
	switch (flag)
	{
	case LEFT:
		if (!OldState._left_controllflag.left)
		{
			return State._left_controllflag.left;
		}
		else
		{
			false;
		}
		break;
	case RIGHT:
		if (!OldState._left_controllflag.right)
		{
			return State._left_controllflag.right;
		}
		else
		{
			false;
		}
		break;
	case UP:
		if (!OldState._left_controllflag.up)
		{
			return State._left_controllflag.up;
		}
		else
		{
			false;
		}
		break;
	case DOWN:
		if (!OldState._left_controllflag.down)
		{
			return State._left_controllflag.down;
		}
		else
		{
			false;
		}
		break;
	}
	return false;
}

bool GamePadXbox::GetButtonPress(int nButton)
{
	return State._buttons[nButton];
}

bool GamePadXbox::GetButtonTrigger(int nButton)
{
	//過去のボタン情報がFalseの時に返す
	switch (nButton)
	{
	case GamePad_Button_DPAD_UP:
		if (!OldState._buttons[GamePad_Button_DPAD_UP])
		{
			return State._buttons[GamePad_Button_DPAD_UP];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_DPAD_DOWN:
		if (!OldState._buttons[GamePad_Button_DPAD_DOWN])
		{
			return State._buttons[GamePad_Button_DPAD_DOWN];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_DPAD_LEFT:
		if (!OldState._buttons[GamePad_Button_DPAD_LEFT])
		{
			return State._buttons[GamePad_Button_DPAD_LEFT];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_DPAD_RIGHT:
		if (!OldState._buttons[GamePad_Button_DPAD_RIGHT])
		{
			return State._buttons[GamePad_Button_DPAD_RIGHT];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_START:
		if (!OldState._buttons[GamePad_Button_START])
		{
			return State._buttons[GamePad_Button_START];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_BACK:
		if (!OldState._buttons[GamePad_Button_BACK])
		{
			return State._buttons[GamePad_Button_BACK];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_LEFT_THUMB:
		if (!OldState._buttons[GamePad_Button_LEFT_THUMB])
		{
			return State._buttons[GamePad_Button_LEFT_THUMB];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_RIGHT_THUMB:
		if (!OldState._buttons[GamePad_Button_RIGHT_THUMB])
		{
			return State._buttons[GamePad_Button_RIGHT_THUMB];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_LEFT_SHOULDER:
		if (!OldState._buttons[GamePad_Button_LEFT_SHOULDER])
		{
			return State._buttons[GamePad_Button_LEFT_SHOULDER];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_RIGHT_SHOULDER:
		if (!OldState._buttons[GamePad_Button_RIGHT_SHOULDER])
		{
			return State._buttons[GamePad_Button_RIGHT_SHOULDER];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_A:
		if (!OldState._buttons[GamePad_Button_A])
		{
			return State._buttons[GamePad_Button_A];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_B:
		if (!OldState._buttons[GamePad_Button_B])
		{
			return State._buttons[GamePad_Button_B];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_X:
		if (!OldState._buttons[GamePad_Button_X])
		{
			return State._buttons[GamePad_Button_X];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_Y:
		if (!OldState._buttons[GamePad_Button_Y])
		{
			return State._buttons[GamePad_Button_Y];
		}
		else
		{
			return false;
		}
		break;
	default:
		return false;
		break;
	}
}

bool GamePadXbox::GetButtonRelease(int nButton)
{
	//過去のボタン情報がTrueの時と現在のボタン情報がFALSEの時にTRUE返す
	switch (nButton)
	{
	case GamePad_Button_DPAD_UP:
		if (OldState._buttons[GamePad_Button_DPAD_UP] == true && State._buttons[GamePad_Button_DPAD_UP] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_DPAD_DOWN:
		if (OldState._buttons[GamePad_Button_DPAD_DOWN] == true && State._buttons[GamePad_Button_DPAD_DOWN] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_DPAD_LEFT:
		if (OldState._buttons[GamePad_Button_DPAD_LEFT] == true && State._buttons[GamePad_Button_DPAD_LEFT] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_DPAD_RIGHT:
		if (OldState._buttons[GamePad_Button_DPAD_RIGHT] == true && State._buttons[GamePad_Button_DPAD_RIGHT] == false)
		{
			return State._buttons[GamePad_Button_DPAD_RIGHT];
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_START:
		if (OldState._buttons[GamePad_Button_START] == true && State._buttons[GamePad_Button_START] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_BACK:
		if (OldState._buttons[GamePad_Button_BACK] == true && State._buttons[GamePad_Button_BACK] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_LEFT_THUMB:
		if (OldState._buttons[GamePad_Button_LEFT_THUMB] == true && State._buttons[GamePad_Button_LEFT_THUMB] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_RIGHT_THUMB:
		if (OldState._buttons[GamePad_Button_RIGHT_THUMB] == true && State._buttons[GamePad_Button_RIGHT_THUMB] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_LEFT_SHOULDER:
		if (OldState._buttons[GamePad_Button_LEFT_SHOULDER] == true && State._buttons[GamePad_Button_LEFT_SHOULDER] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_RIGHT_SHOULDER:
		if (OldState._buttons[GamePad_Button_RIGHT_SHOULDER] == true && State._buttons[GamePad_Button_RIGHT_SHOULDER] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_A:
		if (OldState._buttons[GamePad_Button_A] == true && State._buttons[GamePad_Button_A] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_B:
		if (OldState._buttons[GamePad_Button_B] == true && State._buttons[GamePad_Button_B] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_X:
		if (OldState._buttons[GamePad_Button_X] == true && State._buttons[GamePad_Button_X] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case GamePad_Button_Y:
		if (OldState._buttons[GamePad_Button_Y] == true && State._buttons[GamePad_Button_Y] == false)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	default:
		return false;
		break;
	}
}
