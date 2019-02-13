#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "XInput.lib")

typedef enum
{
	GamePad_Button_DPAD_UP = 0,
	GamePad_Button_DPAD_DOWN = 1,
	GamePad_Button_DPAD_LEFT = 2,
	GamePad_Button_DPAD_RIGHT = 3,
	GamePad_Button_START = 4,
	GamePad_Button_BACK = 5,
	GamePad_Button_LEFT_THUMB = 6,
	GamePad_Button_RIGHT_THUMB = 7,
	GamePad_Button_LEFT_SHOULDER = 8,
	GamePad_Button_RIGHT_SHOULDER = 9,
	GamePad_Button_A = 10,
	GamePad_Button_B = 11,
	GamePad_Button_X = 12,
	GamePad_Button_Y = 13,
	GamePadButton_Max = 14
}GamePadButton;

typedef enum
{
	GamePadIndex_One = 0,
	GamePadIndex_Two = 1,
	GamePadIndex_Three = 2,
	GamePadIndex_Four = 3,
}GamePadIndex;

struct Vector2
{
	double x;
	double y;

	void set(double amount)
	{
		x = y = amount;
	}
};

struct ControllerFlag
{
	bool up;
	bool down;
	bool left;
	bool right;

	void set(bool flag)
	{
		up = down = left = right = flag;
	}
};

struct GamePadState
{
	bool		_buttons[GamePadButton_Max];
	Vector2 	_left_thumbstick;
	Vector2	    _right_thumbstick;
	float		_left_trigger;
	float		_right_trigger;
	ControllerFlag _left_controllflag;

	void reset()
	{
		for (int i = 0; i<(int)GamePadButton_Max; ++i) _buttons[i] = false;
		_left_thumbstick.set(0.0f);
		_right_thumbstick.set(0.0f);
		_left_controllflag.set(false);
		_left_trigger = _right_trigger = 0.0f;
	}
};

typedef enum {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
}LeftControllFlag;

class GamePadXbox
{
public:
	GamePadXbox(GamePadIndex player, int player_number_)
	{
		player_ = player_number_;
		_playerIndex = player;
		State.reset();
	}

	virtual ~GamePadXbox(void)
	{
		if (is_connected()) vibrate(0.0f, 0.0f);
	}

	bool is_connected();
	void vibrate(float leftmotor = 0.0f, float rightmotor = 0.0f);
	void update();
	GamePadState GetState();
	bool GetLeftControllerTrigger(int flag);
	bool GetButtonPress(int nButton);
	bool GetButtonTrigger(int nButton);
	bool GetButtonRelease(int nButton);
private:
	GamePadState	State;
	GamePadState	OldState;
	int player_;
	DWORD _controllerNum;
	XINPUT_STATE _controllerState;
	GamePadIndex _playerIndex;

};