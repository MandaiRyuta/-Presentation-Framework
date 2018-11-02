#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"

class BossEnemySkill01;
class BossEnemySkill02;
class BossEnemySkill03;

class BossEnemySkillManager
{
public:
	BossEnemySkillManager() {}
	~BossEnemySkillManager() {}
public:
	void Init();
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation);
	void Uninit();
private:
	BossEnemySkill01* skill01_;
	BossEnemySkill02* skill02_;
	BossEnemySkill03* skill03_;
};