#include "PlayerBuff.h"
#include "../Player.h"
#include "../../../../InputManager/input.h"

PlayerBuff::PlayerBuff(Player * _player)
	: FrameCounter_(0)
{
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
		buffpattern_ = BUFFSTATE;
	}

	if (buffpattern_ == BUFFSTATE)
	{
		if (FrameCounter_ < 350)
		{
			FrameCounter_++;
		}
		else
		{
			FrameCounter_ = 0;
			buffpattern_ = NONE;
		}
	}
}
