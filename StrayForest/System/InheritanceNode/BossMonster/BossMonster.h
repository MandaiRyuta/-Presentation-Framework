#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../../../Entity/Entity.h"

class BossMonsterAttackPattern;
class BossMonsterSkillPattern;
class BossMonsterMagicPattern;
class BossMonsterPattern;

class BossMonster : public GameObjectManager
{
public:
	BossMonster() 
		: GameObjectManager(0) 
	{}
	~BossMonster() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
public:
	void Damage(double _damage);
	void SetAttack(double _animtrack, float _speed);
	void SetMagic(double _animtrack, float _speed);
	void SetSkill(double _animtrack, float _speed);
private:
	void ChangeBossMonsterMovePattern(BossMonsterPattern* _bossmonsterpattern);
	void ChangeBossMonsterSkillPattern(BossMonsterSkillPattern* _bossmonsterskillpattern);
	void ChangeBossMonsterMagicPattern(BossMonsterMagicPattern* _bossmonstermagicpattern);
	void ChangeBossMonsterAttackPattern(BossMonsterAttackPattern* _bossmonsterattackpattern);
public:
	const double GetLife() const { return status_.health_amount; }
	const double GetMana() const { return status_.mana_amount; }
	const double GetMaxLife() const { return 1000.0; }
	const double GetMaxMana() const { return 800.0; }
public:
	D3DXVECTOR3& Position() { return position_; }
	const double& Life() const { return 500.0; }
	const double& MaxLife() const { return 200.0; }
public:
	static BossMonster* Create();
private:
	BossMonsterAttackPattern* attack_;
	BossMonsterSkillPattern* skill_;
	BossMonsterMagicPattern* magic_;
	BossMonsterPattern* bosspattern_;

	Entity::BOSSSTATUS status_;
	Entity::BOSSMOVESTATE movestate_;
	Entity::MATRIX3D matrix_;
	
	D3DXVECTOR3 scale_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 rotation_;
	CSkinMesh* skinmesh_;
};