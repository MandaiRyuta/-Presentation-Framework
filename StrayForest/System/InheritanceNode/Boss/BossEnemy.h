#pragma once
#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "BossAttack\BossAttackDamageManager.h"
#include "BossSkill\BossEnemySkillManager.h"
#include "BossMagic\BossEnemyMagicManager.h"
#include "BossEnemyMoveManager.h"
#include "BossEnemyStateManager.h"

class BossEnemy : public GameObjectManager
{
public:
	BossEnemy(double _Health, double _mana) : GameObjectManager(0) {}
	~BossEnemy() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	static BossEnemy* Create(double _Health, double _mana);
	static D3DXMATRIX GetBossMatrix();
private:
	CSkinMesh* skinmesh_;
	D3DXVECTOR3 scale_;
	BossEnemyMoveManager* move_;
	BossAttackDamageManager* attack_;
	BossEnemySkillManager* skill_;
	BossEnemyMagicManager* magic_;
	BossEnemyStatusManager* state_;
	Entity::MATRIX3D matrix_;
	static D3DXMATRIX world_;
};