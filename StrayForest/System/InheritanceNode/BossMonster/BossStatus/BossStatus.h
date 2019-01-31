#pragma once
#include "BossStatusManager.h"
#include "../../../Entity/Entity.h"
#include "../../../../GameObjectManager/GameObjectManager.h"
#include "../../../Polygon3D.h"
#include "../../../Polygon2D.h"
#include "../../../colision/SphereColision.h"

class BossStatus : public BossStatusManager
{
public:
	explicit BossStatus();
	virtual ~BossStatus();
	virtual void Update(BossMonster* _bossmonster);
private:
	SphereColision attackcolision_;
	Entity::SphereColision attackcheck_;
	int frame_;
	bool effectdrawflag_;
};