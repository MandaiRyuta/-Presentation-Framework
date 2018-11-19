#include "PlayerNomalAttack.h"
#include "../Player.h"
#include "../../../../InputManager/input.h"

PlayerNomalAttack::PlayerNomalAttack(Player * _player)
	: FrameCounter_(0)
{

}

void PlayerNomalAttack::Update(Player * _player)
{
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_1))
	{
		attackpattern_ = ATTACK01;
		_player->GetSkinMesh()->SetAnimSpeed(2.0f);
		_player->GetSkinMesh()->MyChangeAnim(10.8);
		FrameCounter_ = 0;
	}
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_2))
	{
		attackpattern_ = ATTACK02;
		_player->GetSkinMesh()->SetAnimSpeed(2.0f);
		_player->GetSkinMesh()->MyChangeAnim(12.5);
		FrameCounter_ = 0;
	}
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_3))
	{
		attackpattern_ = ATTACK03;
		_player->GetSkinMesh()->SetAnimSpeed(2.0f);
		_player->GetSkinMesh()->MyChangeAnim(14.7);
		FrameCounter_ = 0;
	}
	switch (attackpattern_)
	{
	case ATTACK01:
		if (FrameCounter_ < 70)
		{
			FrameCounter_++;
		}
		else
		{
			FrameCounter_ = 0;
		}
		break;
	case ATTACK02:
		if (FrameCounter_ < 70)
		{
			FrameCounter_++;
		}
		else
		{
			FrameCounter_ = 0;
		}
		break;
	case ATTACK03:
		if (FrameCounter_ < 140)
		{
			FrameCounter_++;
		}
		else
		{
			FrameCounter_ = 0;
		}
		break;
	default:
		break;
	}
}
