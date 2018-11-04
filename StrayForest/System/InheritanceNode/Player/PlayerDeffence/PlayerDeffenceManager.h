#pragma once
#include "../../../../SkinMeshAnimation/ModelAnim.h"

class PlayerDeffenceManager
{
public:
	PlayerDeffenceManager() {}
	virtual ~PlayerDeffenceManager() {}
public:
	virtual void Update(CSkinMesh* _skinmesh) = 0;
};