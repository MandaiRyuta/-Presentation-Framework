#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../../../Entity/Entity.h"
#include "../../colision/SphereColision.h"

class BossStatusManager;
class BossMonsterAttackPattern;
class BossMonsterSkillPattern;
class BossMonsterMagicPattern;
class BossMonsterPattern;
class SphereColision;

class BossMonster : public GameObjectManager
{
public:
	BossMonster(float _Max_Life, float _Max_Mana);
	~BossMonster() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
public:
	void Damage(float _damage, D3DXVECTOR3 knockback);
	void SetPosition(D3DXVECTOR3 _pos);
	void SetRotation(float _rotation);
	void SetMoveFlagON();
	void SetMagicCoolTime(int _MagicCoolTime);
	void SetMagicPositionFlag(bool _SetMagicPositionFlag);
	void SetCameraMoveFlag(bool _cameraflag);
	void SetKnockBackFlag(bool _knockbackflag);
public:
	void ChangeBossMonsterMovePattern(int _pattern, BossMonsterPattern* _bossmonsterpattern);
	void ChangeBossMonsterSkillPattern(BossMonsterSkillPattern* _bossmonsterskillpattern);
	void ChangeBossMonsterMagicPattern(BossMonsterMagicPattern* _bossmonstermagicpattern);
	void ChangeBossMonsterAttackPattern(BossMonsterAttackPattern* _bossmonsterattackpattern);
public:
	void SetAxisMove(D3DXVECTOR3 _AxisMove);
	D3DXVECTOR3 GetAxisMove();
	bool GetMagicPositionFlag();
	bool GetMagicFlag();
	bool GetMoveFlag();
	bool GetCameraMoveFlag();
	bool GetknockbackFlag();
	D3DXVECTOR3 Getknockback();
	int GetMagicCoolTime();
	const float GetLife() const { return life_; }
	const float GetMana() const { return mana_; }
	const float GetMaxLife() const { return max_life_; }
	const float GetMaxMana() const { return max_mana_; }
	static D3DXVECTOR3 GetPosition();
	static D3DXMATRIX GetRotation() { return GetRotation_; }
	D3DXMATRIX& GetPositionMatrix();
	CSkinMesh* GetSkinMesh();
	float& GetMoveLowSpeed();
	float& GetMoveHighSpeed();
	float& GetMoveMiddleSpeed();
	float& GetMoveVariableSpeed();
	bool GetMoveColisionCheck();
	int GetStateNum();
public:
	D3DXVECTOR3& Position() { return position_; }
public:
	static BossMonster* Create(int _Max_Life, int _Max_Mana);
private:
	bool knockbackflag_;
	D3DXVECTOR3 knockback_;
	int StateNum_;
	BossStatusManager* statusmanager_;;
	BossMonsterAttackPattern* attack_;
	BossMonsterSkillPattern* skill_;
	BossMonsterMagicPattern* magic_;
	BossMonsterPattern* bosspattern_;
	SphereColision* movecolision_;
	Entity::SphereColision movecolisioninfo_;
	float basic_lowspeed_;
	float variable_movespeed_;
	float basic_middlespeed_;
	float basic_highspeed_;

	Entity::BOSSSTATUS status_;
	Entity::BOSSMOVESTATE movestate_;
	Entity::MATRIX3D matrix_;
	static Entity::MATRIX3D GetMatrix_;
	static D3DXVECTOR3 GetPos_;
	static D3DXMATRIX GetRotation_;
	D3DXVECTOR3 AxisMove_;
	D3DXVECTOR3 scale_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 rotation_;
	CSkinMesh* skinmesh_;
	bool cameraflag_;
	int camerastartcount_;
	int MagicCoolTime_;
	bool magicpositonflag_;
	bool magicflag_;
	float mana_;
	float max_mana_;
	float life_;
	float max_life_;
	bool movestatecheck_;
	bool movecheckcolision_;
};