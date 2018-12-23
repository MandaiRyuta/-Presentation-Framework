#include "PlayerMagic.h"
#include "../Player.h"
#include "../../../../InputManager/input.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../MagicObject/MagicObject.h"
#include "../../BossMonster/BossMonster.h"
PlayerMagic::PlayerMagic(Player * _player)
	: FrameCounter_(0)
	, EffectAddHeight(3.0f)
{
	_player = _player;
}

PlayerMagic::~PlayerMagic()
{
}

void PlayerMagic::Update(Player * _player)
{

	if (_player->GetKeyboard()->GetKeyTrigger(DIK_4))
	{
		//SceneGame::GetPlayerMagicEfk()->SetPosition(D3DXVECTOR3(_player->GetPlayerPosMatrix()._41, _player->GetPlayerPosMatrix()._42 + EffectAddHeight, _player->GetPlayerPosMatrix()._43));
		//SceneGame::GetPlayerMagicEfk()->SetIsDrawing(true);
		//SceneGame::GetPlayerMagicEfk()->SetFrameCount(0.2f);
		MagicObject::StartMagic(BossMonster::GetPosition(), D3DXVECTOR3(_player->GetPlayerPosMatrix()._41, _player->GetPlayerPosMatrix()._42 + EffectAddHeight, _player->GetPlayerPosMatrix()._43));
		_player->SetActionPattern(MAGIC01);
		_player->GetSkinMesh()->SetAnimSpeed(2.0f);
		_player->GetSkinMesh()->MyChangeAnim(21.5);
		
		FrameCounter_ = 0;
	}
	if (_player->GetKeyboard()->GetKeyTrigger(DIK_5))
	{
		_player->SetActionPattern(MAGIC02);
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
			//SceneGame::GetPlayerMagicEfk()->SetIsDrawing(false);
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
