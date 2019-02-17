#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XInput.h>

#pragma comment(lib, "XInput.lib")
//ボタン指定用
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
//ゲームパットの数指定
typedef enum
{
	GamePadIndex_One = 0,
	GamePadIndex_Two = 1,
	GamePadIndex_Three = 2,
	GamePadIndex_Four = 3,
}GamePadIndex;

//パッドの軸計算に使う構造体
struct Vector2
{
	double x;
	double y;

	//@Summary	set	:	引数で指定した数値に変数を設定する関数
	//@ParamName	=	"amount"	:	量
	void set(double amount)
	{
		x = y = amount;
	}
};
//スティックのトリガー情報用の構造体
struct ControllerFlag
{
	bool up;
	bool down;
	bool left;
	bool right;

	//@Summary	set	:	引数で指定したフラグに変数を設定する関数
	//@ParamName	=	"flag"	:	true(倒れている）	false(倒れていない)
	void set(bool flag)
	{
		up = down = left = right = flag;
	}
};
//ゲームパッドの構造体
struct GamePadState
{
	bool		_buttons[GamePadButton_Max];
	Vector2 	_left_thumbstick;
	Vector2	    _right_thumbstick;
	float		_left_trigger;
	float		_right_trigger;
	ControllerFlag _left_controllflag;

	//@Summary	reset	:	リセット関数(初期化)
	void reset()
	{
		for (int i = 0; i<(int)GamePadButton_Max; ++i) _buttons[i] = false;
		_left_thumbstick.set(0.0f);
		_right_thumbstick.set(0.0f);
		_left_controllflag.set(false);
		_left_trigger = _right_trigger = 0.0f;
	}
};
//左パッドの番号振り	トリガー時に使用
typedef enum {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
}LeftControllFlag;

class GamePadXbox
{
public:
	//@Summary GamePadXBox	:	ゲームパッドの番号（例：1P,2P,3Pなどプレイヤー指定する為）
	//@ParamName	=	"player"	:	各プレイヤー毎のコントローラー情報指定
	//@ParamName	=	"player_number"	:	プレイヤーの番号振り
	GamePadXbox(GamePadIndex player, int player_number_)
	{
		player_ = player_number_;
		_playerIndex = player;
		State.reset();
	}
	//@Summary	~GamePadXbox	:	開放処理
	virtual ~GamePadXbox(void)
	{
		if (is_connected()) vibrate(0.0f, 0.0f);
	}
	//@Summary	is_connected	:	接続確認関数
	bool is_connected();
	//@Summary	vibrate	:	振動指定関数
	//@ParamName	=	"leftmotor"	左側の振動数
	//@ParamName	=	"rightmotor"右側の振動数
	void vibrate(float leftmotor = 0.0f, float rightmotor = 0.0f);
	//@Summary update	:	更新関数
	void update();
	//@Summary GetState	:	ゲームパッドの現在情報を取得する関数
	GamePadState GetState();
	//@Summary	GetLeftControllerTrigger	:	左スティックの倒れた方向の情報を取得する関数
	//@ParamName	=	"axis"	:	スティックの倒れた軸
	bool GetLeftControllerTrigger(LeftControllFlag axis);
	//@Summary	GetButtonPress	:	ボタンが押されたときの情報を取得する関数
	//@ParamName	=	"nButton"	:	ボタン番号
	bool GetButtonPress(GamePadButton nButton);
	//@Summary	GetButtonTrigger	:	ボタンが最初に押された時の情報を取得する関数
	//@ParamName	=	"nButton"	:	ボタン番号
	bool GetButtonTrigger(GamePadButton nButton);
	//@Summary	GetButtonRelease	:	ボタンの解放
	//@ParamName	=	"nButton"	:	ボタン番号
	bool GetButtonRelease(GamePadButton nButton);
private:
	GamePadState	State;	//ゲームパッドの現在の情報
	GamePadState	OldState;	//ゲームパッドの過去の情報
	int player_;	//プレイヤー番号
	DWORD _controllerNum;	//コントローラーの数
	XINPUT_STATE _controllerState;	//XINPUT情報
	GamePadIndex _playerIndex;	//プレイヤー番号毎のゲームパッド情報
};