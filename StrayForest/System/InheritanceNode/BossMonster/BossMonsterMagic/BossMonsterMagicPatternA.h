#pragma once
#include "BossMonsterMagicPattern.h"
#include "../../../Entity/Entity.h"
#include "../../../colision/SphereColision.h"

class BossMonsterMagicPatternA : public BossMonsterMagicPattern
{
public:
	BossMonsterMagicPatternA();
	~BossMonsterMagicPatternA();
	void Update(BossMonster* _bossmonster) override;
private:
	int FrameCount_;
	int MagicEffectTime_;
	bool MagicSetFlag_;
	bool MagicEffectDrawFlag_;
	bool MagicEffectFlag_;
	D3DXVECTOR3 Position_;
	bool Damegecheck_;
	bool GetDamegeFlag_;
	SphereColision colision_;
	Entity::SphereColision spherecolision_;
};