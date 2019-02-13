#pragma once
#include "BossMonsterMagicPattern.h"
#include "../../../Entity/Entity.h"
#include "../../../colision/SphereColision.h"

class BossMonsterMagicPatternB : public BossMonsterMagicPattern
{
public:
	BossMonsterMagicPatternB();
	~BossMonsterMagicPatternB();
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;
	bool MagicSetFlag_;
	bool MagicEffectDrawFlag_;
	D3DXVECTOR3 Position_;
	bool Damegecheck_;
	bool ColisionCheck_;
	bool GetDamegeFlag_;
	SphereColision colision_;
	Entity::SphereColision spherecolision_;
};