#pragma once
#include "../../../Entity/Entity.h"
#include "../../../InputManager/XBoxController.h"
#include "../../../GameObjectManager/GameObjectManager.h"
//#include "../../../InputManager/input.h"
class PlayerMoveManager;
class PlayerMagicManager;
class PlayerAttackManager;
class PlayerDiffenceManager;
class PlayerBuffStateManager;
class PlayerStateManager;
//class ItemList;
class SphereColision;
class CSkinMesh;

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
	void Damage(float _damage, D3DXVECTOR3 knockback);
	void UseMana(float _mana);
	void Heal(double _animtrack, float _speed, int _amount);
	void Attack(double _animtrack, double _speed);
	void Skill(double _animtrack, double _speed);
	void Magic(double _animtrack, double _speed);
	void Buff(double _animtrack, double _speed);
	void DeBuff(double _animtrack, double _speed);
public:
	static Player* Create(float max_health, float max_mana, float health, float mana);
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
	bool GetSphereColisionFlag();
	Entity::SphereColision GetSphereColisionInfo();
	CSkinMesh* GetSkinMesh();
	//CInputKeyboard* GetKeyboard();
	GamePadXbox* GetGamePad();
public:
	void SetPlayerPosition(D3DXVECTOR3 _pos);
	void SetPlayerMatrix(D3DXMATRIX _world);
	void SetPlayerPosMatrix(D3DXMATRIX _pos);
	void SetPlayerRotMatrix(D3DXMATRIX _rot);
	void SetActionPattern(ACTIONPATTERN _action);
	void SetStateMode(bool _StateMode);
	void SetDiffenceMode(bool _diffence);
	void SetOldPosition(D3DXVECTOR3 _pos);
	void SetKeyframe(int _keyframe);
	void SetCameraMove(bool _cameraflag);
	void SetOldPosFrame(int _oldposframe);
	void SetRotation(float _rotation);
	void SetActionUseFlag(bool _actionusecheck);
	void SetMobileMotion(bool _mobilemotion);
	bool GetCameraMove();
	void addLife(float _Life);
	void addmana(float _Mana);
	int GetKeyframe();
	int GetOldPosFrame();
	bool GetStateMode();
	bool GetDiffenceMode();
	float GetRotation();
	D3DXVECTOR3 GetOldPosition();
	ACTIONPATTERN& GetActionPattern();
	D3DXVECTOR3 GetPlayerPosition();
	bool GetColisionFlag();
	bool GetActionUseFlag();
	D3DXVECTOR3& GetPosition();
	D3DXVECTOR3 Getknokback();
	bool GetMobilemotion();
	Entity::SphereColision& GetColisioninfo();
	static D3DXMATRIX& GetPlayerMatrix();
	static D3DXMATRIX& GetPlayerPosMatrix();
	static D3DXMATRIX& GetPlayerRotMatrix();
	static D3DXMATRIX& GetPlayerBodyMatrix();
	static SphereColision* AttackColision();
private:
	bool mobilemotion_;
	D3DXVECTOR3 knockback_;
	bool MagicUseFlag_;
	bool ActionUseFlag_;
	float rotate_;
	bool movecolisioncheck_;
	Entity::SphereColision moveinfo_;
	GamePadXbox* gamepad_;
	ACTIONPATTERN playeraction_;
	bool cameraflag_;
	bool StateMode_;
	bool Diffence_;
	float Max_Life_;
	float Max_Mana_;
	float Life_;
	float Mana_;
	int keyframe_;
	int oldposframetime_;
	static SphereColision* AttackHitColision_;
	SphereColision* spherecolision_;
	PlayerMoveManager* movemanager_;
	PlayerMagicManager* magicmanager_;
	PlayerAttackManager* attackmanager_;
	PlayerDiffenceManager* diffencemanager_;
	PlayerBuffStateManager* buffmanager_;
	PlayerStateManager* statusmanager_;
	CSkinMesh* skinmesh_;
	//CInputKeyboard* keyboard_;
	D3DXVECTOR3 scale_;
	Entity::MATRIX3D matrix_;
	D3DXVECTOR3 oldPosition_;
	D3DXVECTOR3 position_;
	static D3DXMATRIX body_;
	static D3DXMATRIX world_;
	static D3DXMATRIX pos_;
	static D3DXMATRIX rot_;
};