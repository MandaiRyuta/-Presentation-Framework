#include "BossStatus.h"
#include "../../../SceneManager/InheritanceNode/SceneGame.h"
#include "../../BossMonster/BossMonster.h"
#include "../../../colision/SphereColision.h"
#include "../../../Renderer/GameManager.h"
#include "../../../SceneManager/InheritanceNode/SceneLoseResult.h"
#include "../../MyEffekseer/MyEffekseer.h"

BossStatus::BossStatus()
	: frame_(0)
	, effectdrawflag_(false)
{
}

BossStatus::~BossStatus()
{
}

void BossStatus::Update(BossMonster * _bossmonster)
{
	D3DXVECTOR3 ColisionPlayer, ColisionEnemy;
	bool check;
	D3DXMATRIX LeftHand = SceneGame::GetPlayer()->GetSkinMesh()->GetBoneMatrix("Bip001_001_Bip001_R_Hand");
	D3DXVec3TransformCoord(&ColisionPlayer, &D3DXVECTOR3(0.0f, 3.0f, 0.0f), &LeftHand);
	D3DXVec3TransformCoord(&ColisionEnemy, &D3DXVECTOR3(0.0f, 15.0f, 0.0f), &_bossmonster->GetPositionMatrix());
	
	attackcheck_.colision01.modelpos = ColisionPlayer;
	attackcheck_.colision01.r = 18.0f;
	attackcheck_.colision02.modelpos = ColisionEnemy;
	attackcheck_.colision02.r = 30.0f;

	check = attackcolision_.Collision_detection_of_Sphere_and_Sphere(attackcheck_);
	
	SceneGame::GetDamegeEffectONEfk()->SetScale(D3DXVECTOR3(25.0f, 25.0f, 25.0f));
	SceneGame::GetDamegeEffectONEfk()->SetPosition(ColisionEnemy);
	SceneGame::GetDamegeEffectONEfk()->SetFrameCount(2.0f);

	if (check)
	{
		SceneGame::GetDamegeEffectONEfk()->SetIsDrawing(true);
		_bossmonster->Damage(30.0f);
		effectdrawflag_ = true;
	}
	else
	{
		_bossmonster->Damage(0);
	}

	if (frame_ >= 8)
	{
		effectdrawflag_ = false;
		SceneGame::GetDamegeEffectONEfk()->SetIsDrawing(false);
		frame_ = 0;
	}

	if (_bossmonster->GetLife() < 0.0f)
	{
		GameManager::SetSceneMode(new SceneLoseResult, SCENE_LOSERESULT);
	}

	if (effectdrawflag_)
	{
		frame_++;
	}
}
