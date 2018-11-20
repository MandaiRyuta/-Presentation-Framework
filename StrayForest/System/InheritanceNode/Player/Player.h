#pragma once
#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../SkinMeshAnimation/ModelAnim.h"
#include "../Camera.h"
class CInputKeyboard;
class PlayerMoveManager;
class PlayerMagicManager;
class PlayerAttackManager;
class PlayerBuffStateManager;
class PlayerDiffenceManager;
class ItemList;

class Player : public GameObjectManager
{
public:
	Player();
	~Player() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
public:
	void Damage(int _damage);
	void Heal(double _animtrack, float _speed, int _amount);
	void Attack(double _animtrack, double _speed);
	void Skill(double _animtrack, double _speed);
	void Magic(double _animtrack, double _speed);
	void Buff(double _animtrack, double _speed);
	void DeBuff(double _animtrack, double _speed);
public:
	static Player* Create();
public:
	const int GetLife() const { return Life_; }
	const int GetMana() const { return Mana_; }
	const int GetMaxLife() const { return Max_Life_; }
	const int GetMaxMana() const { return Max_Mana_; }
public:
	void ChangeMovePattern(PlayerMoveManager* _move);
	void ChangeAttackPattern(PlayerMagicManager* _magic);
	void ChangeMagicPattern(PlayerAttackManager* _attack);
	void ChangeBuffMode(PlayerBuffStateManager* _buff);
	void ChangeDiffencePattern(PlayerDiffenceManager* _diffence);
public:
	const int& Life() const { return Life_; }
	const int& Mana() const { return Mana_; }
	const int& MaxLife() const { return Max_Life_; }
	const int& MaxMana() const { return Max_Mana_; }
	CSkinMesh* GetSkinMesh() { return skinmesh_; }
	CInputKeyboard* GetKeyboard();
public:
	void SetPlayerMatrix(D3DXMATRIX _world);
	void SetPlayerPosMatrix(D3DXMATRIX _pos);
	void SetPlayerRotMatrix(D3DXMATRIX _rot);
	void SetActionPattern(ACTIONPATTERN _action);
	void SetStateMode(bool _StateMode);
	bool GetStateMode();
	ACTIONPATTERN& GetActionPattern();
	static D3DXMATRIX& GetPlayerMatrix();
	static D3DXMATRIX& GetPlayerPosMatrix();
	static D3DXMATRIX& GetPlayerRotMatrix();
private:
	ACTIONPATTERN playeraction_;
	bool StateMode_;
	int Max_Life_;
	int Max_Mana_;
	int Life_;
	int Mana_;
	PlayerMoveManager* movemanager_;
	PlayerMagicManager* magicmanager_;
	PlayerAttackManager* attackmanager_;
	PlayerDiffenceManager* diffencemanager_;
	PlayerBuffStateManager* buffmanager_;
	CSkinMesh* skinmesh_;
	CInputKeyboard* keyboard_;
	D3DXVECTOR3 scale_;
	Entity::MATRIX3D matrix_;
	static D3DXMATRIX world_;
	static D3DXMATRIX pos_;
	static D3DXMATRIX rot_;
	ItemList* item_;
};