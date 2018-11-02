#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"

class BossEnemyAttack01;
class BossEnemyAttack02;
class BossEnemyAttack03;

class BossAttackDamageManager
{
public:
	BossAttackDamageManager() {}
	~BossAttackDamageManager() {}
public:
	void Init();
	void Update(CSkinMesh* _skinmesh, D3DXMATRIX& _mtx_position, D3DXMATRIX& _mtx_rotation);
	void Draw();
	void Uninit();
private:
	enum ATTACK_PATTERN
	{
		DEFAULT,	//çUåÇÇµÇ»Ç¢
		ATK_01,
		ATK_02,
		ATK_03,
		NONE,
	};
	BossEnemyAttack01* attack01_;
	BossEnemyAttack02* attack02_;
	BossEnemyAttack03* attack03_;
};