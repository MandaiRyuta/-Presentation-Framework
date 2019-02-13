#pragma once
#include "../../Entity/Entity.h"

class SphereColisionDebug
{
public:
	SphereColisionDebug();
	~SphereColisionDebug();
private:
	struct DEBUG_VERTEX_COLLISION_SPHERE
	{
		D3DXVECTOR3 pos;
		D3DCOLOR color;
	};
public:
	void Draw(const D3DXVECTOR3 & pos, float radius, int type);
private:
	LPD3DXMESH pMesh;
	DEBUG_VERTEX_COLLISION_SPHERE* debugset_;
	Entity::Dx9Buffer buf_;
};