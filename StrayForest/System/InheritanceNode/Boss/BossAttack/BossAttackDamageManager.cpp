#include "BossAttackDamageManager.h"
#include "BossEnemyAttack01.h"
#include "BossEnemyAttack02.h"
#include "BossEnemyAttack03.h"

void BossAttackDamageManager::Init()
{
	attack01_ = new BossEnemyAttack01;
	attack02_ = new BossEnemyAttack02;
	attack03_ = new BossEnemyAttack03;
}

void BossAttackDamageManager::Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation)
{
}

void BossAttackDamageManager::Uninit()
{
	delete attack01_;
	delete attack02_;
	delete attack03_;
}
