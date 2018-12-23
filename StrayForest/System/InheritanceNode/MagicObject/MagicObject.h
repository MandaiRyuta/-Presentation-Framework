#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../Entity/Entity.h"
constexpr int MAGIC_NUM = 10;

class MagicObject : public GameObjectManager
{
public:
	MagicObject(int _Priority);
	~MagicObject();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	static MagicObject* Create(int _Priority);
public:
	static void MoveMagic();
	static void StartMagic(D3DXVECTOR3 target, D3DXVECTOR3 pos);

private:
	static D3DXVECTOR3 TargetVec_;
	static D3DXVECTOR3 OwnerVec_;
	static D3DXVECTOR3 target_;
	static D3DXVECTOR3 pos_;
	static bool flag_;
	static Entity::MAGIC_WORK magic[MAGIC_NUM];
	Entity::MATRIX3D mtx_;
	static D3DXVECTOR3 MovePos[100];
	bool IsDraw_;
	D3DXVECTOR3 dir;
};