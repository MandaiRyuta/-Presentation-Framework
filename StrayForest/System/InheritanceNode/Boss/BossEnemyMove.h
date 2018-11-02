#pragma once
#include "../../../SkinMeshAnimation/ModelAnim.h"
constexpr float ENEMY_MAXHIGHSPEED = 15.0f;
constexpr float ENEMY_MINLOWSPEED = -15.0f;

class BossEnemyMove
{
public:
	BossEnemyMove() {}
	~BossEnemyMove() {}
public:
	void Init(D3DXVECTOR3& _position, D3DXVECTOR3& _rotation, float& _highspeed, float& _lowspeed, bool& _movestate);
	void Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation);
	void Uninit();

	void MoveStateChange(bool& _movestate);
	void SpeedChange(bool& _mode, unsigned short& _addspeed);
private:
	D3DXVECTOR3 position_;
	D3DXVECTOR3 rotation_;
	float basic_highspeed_;
	float basic_lowspeed_;
	float variable_speed_;
	bool movestate_;
};