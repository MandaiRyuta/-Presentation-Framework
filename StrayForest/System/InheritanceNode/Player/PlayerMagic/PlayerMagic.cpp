#include "PlayerMagic.h"
#include "../Player.h"
#include "../../../../InputManager/input.h"

PlayerMagic::PlayerMagic(Player * _player)
	: FrameCounter_(0)
{

}

PlayerMagic::~PlayerMagic()
{
}

void PlayerMagic::Update(Player * _player)
{
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_4))
	{
		_player->SetActionPattern(ACTIONPATTERN::MAGIC01);
		_player->GetSkinMesh()->SetAnimSpeed(2.0f);
		_player->GetSkinMesh()->MyChangeAnim(21.5);
		FrameCounter_ = 0;
	}
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_5))
	{
		_player->SetActionPattern(ACTIONPATTERN::MAGIC02);
		_player->GetSkinMesh()->SetAnimSpeed(2.0f);
		_player->GetSkinMesh()->MyChangeAnim(24);
		FrameCounter_ = 0;
	}

	switch (_player->GetActionPattern())
	{
	case MAGIC01:
		if (FrameCounter_ < 250)
		{
			FrameCounter_++;
		}
		else
		{
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(0.0);
			_player->SetActionPattern(ACTIONPATTERN::STATE);
			FrameCounter_ = 0;
		}
		break;
	case MAGIC02:
		if (FrameCounter_ < 350)
		{
			FrameCounter_++;
		}
		else
		{
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(0.0);
			_player->SetActionPattern(ACTIONPATTERN::STATE);
			FrameCounter_ = 0;
		}
		break;
	default:
		break;
	}
}
