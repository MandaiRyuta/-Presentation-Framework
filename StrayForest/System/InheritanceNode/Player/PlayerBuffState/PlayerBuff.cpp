#include "PlayerBuff.h"
#include "../Player.h"
#include "../../../../InputManager/input.h"

PlayerBuff::PlayerBuff(Player * _player)
	: FrameCounter_(0)
{
	_player = _player;
}

PlayerBuff::~PlayerBuff()
{
}

void PlayerBuff::Update(Player * _player)
{
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_7))
	{
		FrameCounter_ = 0;
		_player->GetSkinMesh()->MyChangeAnim(27.5);
		_player->GetSkinMesh()->SetAnimSpeed(2.0);
		_player->SetActionPattern(ACTIONPATTERN::BUFFSTATE);
	}

	if (_player->GetActionPattern() == ACTIONPATTERN::BUFFSTATE)
	{
		if (FrameCounter_ < 350)
		{
			FrameCounter_++;
		}
		else
		{
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(0.0);
			_player->SetActionPattern(ACTIONPATTERN::STATE);
		}
	}
}
