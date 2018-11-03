#pragma once
#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"

class BossEnemyDeffenceManager;
class BossAttackDamageManager;
class BossEnemySkillManager;
class BossEnemyMagicManager;
class BossEnemyStatusManager;
class BossEnemyMoveManager;
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
	BossEnemyMoveManager* rotate_;

	BossEnemyDeffenceManager* deffence01_;
	BossEnemyDeffenceManager* deffence02_;
	
	BossAttackDamageManager* attack01_;
	BossAttackDamageManager* attack02_;
	BossAttackDamageManager* attack03_;
	
	BossEnemySkillManager* skill01_;
	BossEnemySkillManager* skill02_;
	BossEnemySkillManager* skill03_;
	
	BossEnemyMagicManager* magic01_;
	BossEnemyMagicManager* magic02_;
	BossEnemyMagicManager* magic03_;
	
	BossEnemyStatusManager* healthstate_;
	BossEnemyStatusManager* manastate_;
	BossEnemyStatusManager* powerstate_;
	Entity::BOSSSTATUS status_;
	Entity::BOSSMOVESTATE movestate_;
	Entity::MATRIX3D matrix_;
	static D3DXMATRIX world_;
};