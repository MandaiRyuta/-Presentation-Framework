#include "PlayerDiffence.h"
#include "../../../../InputManager/XBoxController.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Player.h"

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
	if (_player->GetGamePad()->GetButtonTrigger(GamePad_Button_Y))
	{
		FrameCounter_ = 0;
		_player->SetDiffenceMode(true);
		_player->SetActionPattern(ACTIONPATTERN::DSTART);
		_player->GetSkinMesh()->SetAnimSpeed(1.0f);
		_player->GetSkinMesh()->MyChangeAnim(18.7);
		_player->SetKeyframe(0);
		_player->SetActionUseFlag(true);
	}
	else if (_player->GetGamePad()->GetButtonRelease(GamePad_Button_Y))
	{
		FrameCounter_ = 0;
		_player->SetActionUseFlag(false);
		_player->SetDiffenceMode(false);
		_player->GetSkinMesh()->SetAnimSpeed(1.0f);
		_player->GetSkinMesh()->MyChangeAnim(0.0);
		_player->SetKeyframe(0);
		_player->SetActionPattern(ACTIONPATTERN::STATE);
	}

	switch (_player->GetActionPattern())
	{
	case STATE:
		break;
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
