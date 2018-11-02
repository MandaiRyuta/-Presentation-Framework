#pragma once

#include "../../../../SkinMeshAnimation/ModelAnim.h"

class BossEnemyMagic01;
class BossEnemyMagic02;
class BossEnemyMagic03;

class BossEnemyMagicManager
{
public:
	BossEnemyMagicManager() {}
	~BossEnemyMagicManager() {}
public:
	void Init();
	void Update(CSkinMesh * _skinmesh, D3DXMATRIX & _mtx_position, D3DXMATRIX & _mtx_rotation);
	void Uninit();
private:
	enum MAGICPATTERN
	{
		DEFAULT,
		MAGIC01,
		MAGIC02,
		MAGIC03,
		NONE
	};
	BossEnemyMagic01* magic01_;
	BossEnemyMagic02* magic02_;
	BossEnemyMagic03* magic03_;
};