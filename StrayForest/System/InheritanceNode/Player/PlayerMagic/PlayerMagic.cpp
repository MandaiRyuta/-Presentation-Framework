#include "PlayerMagic.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../MyEffekseer/MyEffekseer.h"
#include "../Player.h"
#include "../../../../InputManager/XBoxController.h"
#include "../../MagicObject/MagicObject.h"
#include "../../BossMonster/BossMonster.h"
#include "../../../Renderer/GameManager.h"
#include "../../../System/Sound.h"

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
	if (_player->GetMana() > 430.0f)
	{
		if (_player->GetKeyframe() > 80)
		{
			if (_player->GetGamePad()->GetButtonTrigger(GamePad_Button_X))
			{
				GameManager::GetEffectSound()->PlaySoundA(EffectSound::SOUND_LABEL::SOUND_PLAYERMAGIC);
				_player->SetActionUseFlag(true);
				SceneGame::GetPlayerMagicEfk()->SetScale(D3DXVECTOR3(20.0f, 20.0f, 20.0f));
				SceneGame::GetPlayerMagicEfk()->SetPosition(_player->GetPlayerPosition());
				SceneGame::GetPlayerMagicEfk()->SetIsDrawing(true);
				SceneGame::GetPlayerMagicEfk()->SetFrameCount(1.0f);
				SceneGame::GetMagicEffect()->StartMagic(BossMonster::GetPosition(), _player->GetPlayerPosition());
				_player->SetActionPattern(MAGIC01);
				_player->GetSkinMesh()->SetAnimSpeed(2.0f);
				_player->GetSkinMesh()->MyChangeAnim(24);
				FrameCounter_ = 0;
				_player->SetKeyframe(0);
				/*Mana*/
				_player->UseMana(430.0f);
			}
		}
	}

	switch (_player->GetActionPattern())
	{
	case MAGIC01:
		if (FrameCounter_ < 120)
		{
			if (FrameCounter_ > 60)
			{
				SceneGame::GetPlayerMagicEfk()->SetIsDrawing(false);
			}
			FrameCounter_++;
		}
		else
		{
			_player->GetSkinMesh()->SetAnimSpeed(1.0f);
			_player->GetSkinMesh()->MyChangeAnim(0.0);
			_player->SetActionPattern(ACTIONPATTERN::STATE);
			_player->SetActionUseFlag(false);
			FrameCounter_ = 0;
		}
	default:
		break;
	}
}
