#include "PlayerDiffence.h"
#include "../Player.h"
#include "../../../../InputManager/input.h"

PlayerDiffence::PlayerDiffence(Player * _player)
	: FrameCounter_(0)
{
	_player = _player;
}

PlayerDiffence::~PlayerDiffence()
{
}

void PlayerDiffence::Update(Player * _player)
{
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_6))
	{
		FrameCounter_ = 0;
		_player->SetActionPattern(ACTIONPATTERN::DSTART);
		_player->GetSkinMesh()->SetAnimSpeed(1.0f);
		_player->GetSkinMesh()->MyChangeAnim(18.7);
	}
	else if (_player->GetKeyboard()->GetKeyRelease(DIK_6))
	{
		FrameCounter_ = 0;
		_player->GetSkinMesh()->SetAnimSpeed(1.0f);
		_player->GetSkinMesh()->MyChangeAnim(0.0);
		_player->SetActionPattern(ACTIONPATTERN::STATE);
	}
	switch (_player->GetActionPattern())
	{
	case DSTART:
		if (FrameCounter_ < 60)
		{
			FrameCounter_++;
		}
		else
		{
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(20.5);
			_player->SetActionPattern(ACTIONPATTERN::DEND);
			FrameCounter_++;
		}
		break;
	case DEND:
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(20.5);
			FrameCounter_ = 0;
		break;
	default:
		break;
	}
	
}
