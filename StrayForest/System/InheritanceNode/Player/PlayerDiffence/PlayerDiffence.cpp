#include "PlayerDiffence.h"
#include "../Player.h"
#include "../../../../InputManager/input.h"

PlayerDiffence::PlayerDiffence(Player * _player)
	: FrameCounter_(0)
{
}

PlayerDiffence::~PlayerDiffence()
{
}

void PlayerDiffence::Update(Player * _player)
{
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_6))
	{
		FrameCounter_ = 0;
		diffencepattern_ = START;
		_player->GetSkinMesh()->MyChangeAnim(18.7);
	}
	else if (_player->GetKeyboard()->GetKeyRelease(DIK_6))
	{
		FrameCounter_ = 0;
		diffencepattern_ = NONE;
	}
	switch (diffencepattern_)
	{
	case START:
		if (FrameCounter_ < 60)
		{
			FrameCounter_++;
		}
		else
		{
			_player->GetSkinMesh()->MyChangeAnim(20.5);
			diffencepattern_ = END;
			FrameCounter_++;
		}
		break;
	case END:
			_player->GetSkinMesh()->MyChangeAnim(20.5);
			FrameCounter_ = 0;
		break;
	default:
		break;
	}
	
}
