#pragma once

#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"

class GuardianManager;

constexpr int FRAME_DEF = 60;

class Guardian : public GameObjectManager
{
public:
	Guardian() : GameObjectManager(0) {}
	~Guardian() {}
public:
	enum GUARDIANNUM
	{
		GUARDIAN01,
		GUARDIAN02,
		GUARDIAN03,
		GUARDIAN04,
		GUARDIAN05,
		GUARDIAN06,
		GUARDIAN07,
		GUARDIAN08
	};
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	static Guardian* Create();
private:
	int animtime_;
	GuardianManager* guardians_[10];
	Entity::MATRIX3D matrix_[10];
	D3DXQUATERNION Qrot_[10];
	Entity::Model* model;
	D3DXVECTOR3 vecRot_;
};
