#pragma once
#include "BossStatusManager.h"
#include "../../../Entity/Entity.h"
#include "../../../../GameObjectManager/GameObjectManager.h"
#include "../../../Polygon3D.h"
#include "../../../Polygon2D.h"
#include "../../../colision/SphereColision.h"

class SphereColisionDebug;

class BossStatus : public BossStatusManager
{
public:
	explicit BossStatus();
	virtual ~BossStatus();
	virtual void Update(BossMonster* _bossmonster);
	//ƒeƒXƒg
	void Draw();
private:
	bool damegeactionflag_;
	int damegeactiioncount_;
	bool damegeflag_;
	int damegeframe_;
	float PlayerHitScale_;
	float EnemyHitScale_;
	int damegecount_;
	D3DXVECTOR3 bosshitpos_;
	D3DXVECTOR3 weponcolisionset_;
	SphereColision attackcolision_;
	Entity::SphereColision attackcheck_;
	int frame_;
	bool effectdrawflag_;
	//SphereColisionDebug* attackCheck;
	//SphereColisionDebug* monstercheck_;
};