#include "PlayerState.h"
#include "../../../LoadManager/TextureLoder.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../Player/PlayerItem/PlayerWeapon.h"
#include "../../BossMonster/BossMonster.h"
#include "../../../colision/SphereColision.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Player.h"
#include "../../../Polygon3D.h"
#include "../../../Polygon2D.h"
#include "../../../Renderer/GameManager.h"
#include "../../../SceneManager/InheritanceNode/SceneWinResult.h"

PlayerState::PlayerState(Player* _player)
	: alphacolor_(1)
	, flag_(true)
{
}

PlayerState::~PlayerState()
{
}

void PlayerState::Update(Player * _player)
{
	D3DXVECTOR3 ColisionPlayer,ColisionEnemy;
	bool check;
	//attackcolision_->Collision_detection_of_Sphere_and_Sphere();
	D3DXMATRIX LeftHand = SceneGame::GetBossMonster()->GetSkinMesh()->GetBoneMatrix("Armature_Mutant_LeftHand");
	//D3DXVec3TransformCoord(&weponPosTop, &D3DXVECTOR3(0.0f, 3.0f, 0.0f), &LeftHand);
	D3DXVec3TransformCoord(&ColisionEnemy,&D3DXVECTOR3(0.0f,10.0f,0.0f),&LeftHand);
	D3DXVec3TransformCoord(&ColisionPlayer, &D3DXVECTOR3(0.0f, 60.0f, 0.0f), &_player->GetPlayerPosMatrix());
	attackcheck_.colision01.modelpos = ColisionEnemy;
	attackcheck_.colision01.r = 15.0f;
	attackcheck_.colision02.modelpos = ColisionPlayer;
	attackcheck_.colision02.r = 5.0f;
	check = attackcolision_.Collision_detection_of_Sphere_and_Sphere(attackcheck_);
	if (!_player->GetDiffenceMode())
	{
		if (check)
		{
			_player->Damage(25.0f);
		}
		else
		{
			_player->Damage(0.0f);
		}
	}

	if (_player->GetLife() < _player->GetMaxLife() * 0.45f)
	{
		if (flag_)
		{
			if (alphacolor_ >= 128)
			{
				flag_ = false;
			}
			alphacolor_++;
		}
		else
		{
			if (alphacolor_ <= 1)
			{
				flag_ = true;
			}
			alphacolor_--;
		}
		SceneGame::GetDamegeEffect()->SetColor(D3DCOLOR_RGBA(255, 0, 0, alphacolor_));
	}
	else
	{
		SceneGame::GetDamegeEffect()->SetColor(D3DCOLOR_RGBA(255, 0, 0, 0));
	}

	if (_player->GetLife() < 0.0f)
	{
		GameManager::SetSceneMode(new SceneWinResult, SCENE_WINRESULT);
	}

	_player->addLife(_player->GetMaxLife() * 0.0001f);
	_player->addmana(_player->GetMaxMana() * 0.00005f);
	SceneGame::GetHealthBar()->StatusSetUp(_player->GetLife(), _player->GetMaxLife());

	SceneGame::GetManaBar()->StatusSetUp(_player->GetMana(), _player->GetMaxMana());
}
