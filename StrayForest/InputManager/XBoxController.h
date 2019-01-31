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

// GamePad Indexes
typedef enum
{
	GamePadIndex_One = 0,
	GamePadIndex_Two = 1,
	GamePadIndex_Three = 2,
	GamePadIndex_Four = 3,
}GamePadIndex;
struct Vector2
{
	float x;
	float y;

	void set(float amount)
	{
		x = y = amount;
	}
};
// The GamePad State Stuct, were we store the buttons positions
struct GamePadState
{
	bool		_buttons[GamePadButton_Max];
	Vector2 	_left_thumbstick;               // <= I'm using a Vector2 (floats) class but you can replaced it with a float X and Y or whatever your Vector2 class is
	Vector2	    _right_thumbstick;
	float		_left_trigger;
	float		_right_trigger;
	// Just to clear all values to default
	void reset()
	{
		for (int i = 0; i<(int)GamePadButton_Max; ++i) _buttons[i] = false;
		_left_thumbstick.set(0.0f);
		_right_thumbstick.set(0.0f);
		_left_trigger = _right_trigger = 0.0f;
	}
};

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
		// We don't want the controller to be vibrating accidentally when we exit the app
		if (is_connected()) vibrate(0.0f, 0.0f);
	}

	bool is_connected();
	void vibrate(float leftmotor = 0.0f, float rightmotor = 0.0f);
	void update();
	GamePadState GetState();
private:
	GamePadState	State;
	int player_;
	DWORD _controllerNum;
	XINPUT_STATE _controllerState;
	GamePadIndex _playerIndex;

};