#include "PlayerNomalAttack.h"
#include "../Player.h"
#include "../../../../InputManager/input.h"

PlayerNomalAttack::PlayerNomalAttack(Player * _player)
	: FrameCounter_(0)
{
	_player = _player;
}

void PlayerNomalAttack::Update(Player * _player)
{
	_player->GetSkinMesh()->SetAnimSpeed(2.0f);
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_1))
	{
		_player->GetSkinMesh()->MyChangeAnim(10.8);
		attackpattern_ = ATTACK01;
		FrameCounter_ = 0;
	}
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_2))
	{
		attackpattern_ = ATTACK02;
		_player->GetSkinMesh()->MyChangeAnim(12.5);
		FrameCounter_ = 0;
	}
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_3))
	{
		attackpattern_ = ATTACK03;
		_player->GetSkinMesh()->MyChangeAnim(14.7);
		FrameCounter_ = 0;
	}

	switch (attackpattern_)
	{
	case STATE:
		break;
	case ATTACK01:
		if (FrameCounter_ < 60)
		{
			FrameCounter_++;
		}
		else
		{
			attackpattern_ = STATE;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(0.0);
			FrameCounter_ = 0;
		}
		break;
	case ATTACK02:
		if (FrameCounter_ < 60)
		{
			FrameCounter_++;
		}
		else
		{
			attackpattern_ = STATE;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(0.0);
			FrameCounter_ = 0;
		}
		break;
	case ATTACK03:
		if (FrameCounter_ < 130)
		{
			FrameCounter_++;
		}
		else
		{
			attackpattern_ = STATE;
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(0.0);
			FrameCounter_ = 0;
		}
		break;
	default:
		break;
	}
}
