#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"

class BossEnemyDeffencePattern01;
class BossEnemyDeffencePattern02;

class BossEnemyDeffenceManager
{
public:
	BossEnemyDeffenceManager() {}
	~BossEnemyDeffenceManager() {}
public:
	void Init();
	void Update();
private:
	BossEnemyDeffencePattern01* deffence01_;
	BossEnemyDeffencePattern02* deffence02_;
};