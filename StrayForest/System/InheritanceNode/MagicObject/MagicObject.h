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
	//SphereColision HitColision_;
	static D3DXVECTOR3 TargetVec_[MAGIC_NUM];
	static D3DXVECTOR3 OwnerVec_[MAGIC_NUM];
	static D3DXVECTOR3 target_;
	static D3DXVECTOR3 pos_;
	static Entity::MAGIC_WORK magic[MAGIC_NUM];
};