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
		magicnum_ = MAGIC01;
		_player->GetSkinMesh()->MyChangeAnim(21.5);
		FrameCounter_ = 0;
	}
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_5))
	{
		magicnum_ = MAGIC02;
		_player->GetSkinMesh()->MyChangeAnim(24);
		FrameCounter_ = 0;
	}

	switch (magicnum_)
	{
	case MAGIC01:
		if (FrameCounter_ < 250)
		{
			FrameCounter_++;
		}
		else
		{
			_player->GetSkinMesh()->MyChangeAnim(21.5);
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
			_player->GetSkinMesh()->MyChangeAnim(24);
			FrameCounter_ = 0;
		}
		break;
	default:
		break;
	}
}
