#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XInput.h>

#pragma comment(lib, "XInput.lib")
//�{�^���w��p
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
//�Q�[���p�b�g�̐��w��
typedef enum
{
	GamePadIndex_One = 0,
	GamePadIndex_Two = 1,
	GamePadIndex_Three = 2,
	GamePadIndex_Four = 3,
}GamePadIndex;

//�p�b�h�̎��v�Z�Ɏg���\����
struct Vector2
{
	double x;
	double y;

	//@Summary	set	:	�����Ŏw�肵�����l�ɕϐ���ݒ肷��֐�
	//@ParamName	=	"amount"	:	��
	void set(double amount)
	{
		x = y = amount;
	}
};
//�X�e�B�b�N�̃g���K�[���p�̍\����
struct ControllerFlag
{
	bool up;
	bool down;
	bool left;
	bool right;

	//@Summary	set	:	�����Ŏw�肵���t���O�ɕϐ���ݒ肷��֐�
	//@ParamName	=	"flag"	:	true(�|��Ă���j	false(�|��Ă��Ȃ�)
	void set(bool flag)
	{
		up = down = left = right = flag;
	}
};
//�Q�[���p�b�h�̍\����
struct GamePadState
{
	bool		_buttons[GamePadButton_Max];
	Vector2 	_left_thumbstick;
	Vector2	    _right_thumbstick;
	float		_left_trigger;
	float		_right_trigger;
	ControllerFlag _left_controllflag;

	//@Summary	reset	:	���Z�b�g�֐�(������)
	void reset()
	{
		for (int i = 0; i<(int)GamePadButton_Max; ++i) _buttons[i] = false;
		_left_thumbstick.set(0.0f);
		_right_thumbstick.set(0.0f);
		_left_controllflag.set(false);
		_left_trigger = _right_trigger = 0.0f;
	}
};
//���p�b�h�̔ԍ��U��	�g���K�[���Ɏg�p
typedef enum {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
}LeftControllFlag;

class GamePadXbox
{
public:
	//@Summary GamePadXBox	:	�Q�[���p�b�h�̔ԍ��i��F1P,2P,3P�Ȃǃv���C���[�w�肷��ׁj
	//@ParamName	=	"player"	:	�e�v���C���[���̃R���g���[���[���w��
	//@ParamName	=	"player_number"	:	�v���C���[�̔ԍ��U��
	GamePadXbox(GamePadIndex player, int player_number_)
	{
		player_ = player_number_;
		_playerIndex = player;
		State.reset();
	}
	//@Summary	~GamePadXbox	:	�J������
	virtual ~GamePadXbox(void)
	{
		if (is_connected()) vibrate(0.0f, 0.0f);
	}
	//@Summary	is_connected	:	�ڑ��m�F�֐�
	bool is_connected();
	//@Summary	vibrate	:	�U���w��֐�
	//@ParamName	=	"leftmotor"	�����̐U����
	//@ParamName	=	"rightmotor"�E���̐U����
	void vibrate(float leftmotor = 0.0f, float rightmotor = 0.0f);
	//@Summary update	:	�X�V�֐�
	void update();
	//@Summary GetState	:	�Q�[���p�b�h�̌��ݏ����擾����֐�
	GamePadState GetState();
	//@Summary	GetLeftControllerTrigger	:	���X�e�B�b�N�̓|�ꂽ�����̏����擾����֐�
	//@ParamName	=	"axis"	:	�X�e�B�b�N�̓|�ꂽ��
	bool GetLeftControllerTrigger(LeftControllFlag axis);
	//@Summary	GetButtonPress	:	�{�^���������ꂽ�Ƃ��̏����擾����֐�
	//@ParamName	=	"nButton"	:	�{�^���ԍ�
	bool GetButtonPress(GamePadButton nButton);
	//@Summary	GetButtonTrigger	:	�{�^�����ŏ��ɉ����ꂽ���̏����擾����֐�
	//@ParamName	=	"nButton"	:	�{�^���ԍ�
	bool GetButtonTrigger(GamePadButton nButton);
	//@Summary	GetButtonRelease	:	�{�^���̉��
	//@ParamName	=	"nButton"	:	�{�^���ԍ�
	bool GetButtonRelease(GamePadButton nButton);
private:
	GamePadState	State;	//�Q�[���p�b�h�̌��݂̏��
	GamePadState	OldState;	//�Q�[���p�b�h�̉ߋ��̏��
	int player_;	//�v���C���[�ԍ�
	DWORD _controllerNum;	//�R���g���[���[�̐�
	XINPUT_STATE _controllerState;	//XINPUT���
	GamePadIndex _playerIndex;	//�v���C���[�ԍ����̃Q�[���p�b�h���
};