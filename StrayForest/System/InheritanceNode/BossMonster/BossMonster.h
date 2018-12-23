#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../../../Entity/Entity.h"
#include "../../colision/SphereColision.h"

class BossMonsterAttackPattern;
class BossMonsterSkillPattern;
class BossMonsterMagicPattern;
class BossMonsterPattern;
class SphereColision;

class BossMonster : public GameObjectManager
{
public:
	BossMonster(int _Max_Life, int _Max_Mana);
	~BossMonster() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
public:
	void Damage(int _damage);
	void SetPosition(D3DXVECTOR3 _pos);
	void SetRotation(float _rotation);
	void SetMoveFlagON();
public:
	void ChangeBossMonsterMovePattern(BossMonsterPattern* _bossmonsterpattern);
	void ChangeBossMonsterSkillPattern(BossMonsterSkillPattern* _bossmonsterskillpattern);
	void ChangeBossMonsterMagicPattern(BossMonsterMagicPattern* _bossmonstermagicpattern);
	void ChangeBossMonsterAttackPattern(BossMonsterAttackPattern* _bossmonsterattackpattern);
public:
	const int GetLife() const { return life_; }
	const int GetMana() const { return mana_; }
	const int GetMaxLife() const { return max_life_; }
	const int GetMaxMana() const { return max_mana_; }
	static D3DXVECTOR3 GetPosition() { return GetPos_; }
	static D3DXMATRIX GetRotation() { return GetRotation_; }
	D3DXMATRIX& GetPositionMatrix();
	CSkinMesh* GetSkinMesh();
	SphereColision* GetMoveColision();
	Entity::SphereColision& GetMoveColisionInfo();
	float& GetMoveLowSpeed();
	float& GetMoveHighSpeed();
	float& GetMoveVariableSpeed();
	const bool& GetMoveHitColision();
public:
	D3DXVECTOR3& Position() { return position_; }
	const int& Life() const { return life_; }
	const int& Mana() const { return mana_; }
	const int& MaxLife() const { return max_life_; }
	const int& MaxMana() const { return max_mana_; }
public:
	static BossMonster* Create(int _Max_Mana, int _Max_Life);
private:
	BossMonsterAttackPattern* attack_;
	BossMonsterSkillPattern* skill_;
	BossMonsterMagicPattern* magic_;
	BossMonsterPattern* bosspattern_;
	SphereColision* movecolision_;
	Entity::SphereColision movecolisioninfo_;
	float basic_lowspeed_;
	float variable_movespeed_;
	float basic_highspeed_;

	Entity::BOSSSTATUS status_;
	Entity::BOSSMOVESTATE movestate_;
	Entity::MATRIX3D matrix_;
	static Entity::MATRIX3D GetMatrix_;
	static D3DXVECTOR3 GetPos_;
	static D3DXMATRIX GetRotation_;
	D3DXVECTOR3 scale_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 rotation_;
	CSkinMesh* skinmesh_;

	int mana_;
	int max_mana_;
	int life_;
	int max_life_;
	bool movestatecheck_;
	bool movecheckcolision_;
};