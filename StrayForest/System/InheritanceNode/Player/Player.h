#pragma once
#include "../../../Entity/Entity.h"
#include "../../../InputManager/input.h"
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Camera.h"
class PlayerMoveManager;
class PlayerMagicManager;
class PlayerAttackManager;
class PlayerDiffenceManager;
class PlayerBuffStateManager;
class PlayerStateManager;
//class ItemList;
class SphereColision;

class Player : public GameObjectManager
{
public:
	Player(float max_health, float max_mana, float health, float mana);
	~Player() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
public:
	void Damage(float _damage);
	void UseMana(float _mana);
	void Heal(double _animtrack, float _speed, int _amount);
	void Attack(double _animtrack, double _speed);
	void Skill(double _animtrack, double _speed);
	void Magic(double _animtrack, double _speed);
	void Buff(double _animtrack, double _speed);
	void DeBuff(double _animtrack, double _speed);
public:
	static Player* Create(int max_health, int max_mana, int health, int mana);
public:
	float GetLife() const { return Life_; }
	float GetMana() const { return Mana_; }
	const float GetMaxLife() const { return Max_Life_; }
	const float GetMaxMana() const { return Max_Mana_; }
public:
	void ChangeMovePattern(PlayerMoveManager* _move);
	void ChangeAttackPattern(PlayerAttackManager* _attack);
	void ChangeMagicPattern(PlayerMagicManager* _magic);
	void ChangeBuffMode(PlayerBuffStateManager* _buff);
	void ChangeDiffencePattern(PlayerDiffenceManager* _diffence);
public:
	CSkinMesh* GetSkinMesh();
	CInputKeyboard* GetKeyboard();
public:
	void SetPlayerMatrix(D3DXMATRIX _world);
	void SetPlayerPosMatrix(D3DXMATRIX _pos);
	void SetPlayerRotMatrix(D3DXMATRIX _rot);
	void SetActionPattern(ACTIONPATTERN _action);
	void SetStateMode(bool _StateMode);
	void SetDiffenceMode(bool _diffence);
	void SetOldPosition(D3DXVECTOR3 _pos);
	void SetKeyframe(int _keyframe);
	void addLife(float _Life);
	void addmana(float _Mana);
	int GetKeyframe();
	bool GetStateMode();
	bool GetDiffenceMode();
	D3DXVECTOR3 GetOldPosition();
	ACTIONPATTERN& GetActionPattern();
	static D3DXMATRIX& GetPlayerMatrix();
	static D3DXMATRIX GetPlayerPosMatrix();
	static D3DXMATRIX& GetPlayerRotMatrix();
	static D3DXMATRIX& GetPlayerBodyMatrix();
	static SphereColision* AttackColision();
private:
	ACTIONPATTERN playeraction_;
	bool StateMode_;
	bool Diffence_;
	float Max_Life_;
	float Max_Mana_;
	float Life_;
	float Mana_;
	int keyframe_;
	static SphereColision* AttackHitColision_;
	SphereColision* spherecolision_;
	PlayerMoveManager* movemanager_;
	PlayerMagicManager* magicmanager_;
	PlayerAttackManager* attackmanager_;
	PlayerDiffenceManager* diffencemanager_;
	PlayerBuffStateManager* buffmanager_;
	PlayerStateManager* statusmanager_;
	CSkinMesh* skinmesh_;
	CInputKeyboard* keyboard_;
	D3DXVECTOR3 scale_;
	Entity::MATRIX3D matrix_;
	D3DXVECTOR3 oldPosition_;
	static D3DXMATRIX body_;
	static D3DXMATRIX world_;
	static D3DXMATRIX pos_;
	static D3DXMATRIX rot_;
	//ItemList* item_;
};