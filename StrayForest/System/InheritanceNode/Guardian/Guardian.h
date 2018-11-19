#pragma once

#include "../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"

class GuardianManager;

constexpr int FRAME_DEF = 60;

class Guardian : public GameObjectManager
{
public:
	Guardian()
		: GameObjectManager(0)
		, FrameCount_(0.0f)
	{}
	~Guardian() {}
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	static Guardian* Create();
private:
	float FrameCount_;
	Entity::MATRIX3D matrix_[10];
	D3DXQUATERNION Qrot_[10];
	Entity::Model* model;
	D3DXVECTOR3 vecRot_;
};
