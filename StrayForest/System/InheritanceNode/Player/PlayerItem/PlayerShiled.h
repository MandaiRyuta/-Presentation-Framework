#pragma once

#include "../../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"

class Shiled : public GameObjectManager
{
public:
	Shiled(int _Priority) : GameObjectManager(_Priority)
	{
		position_ = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
		scale_ = D3DXVECTOR3(15.0f, 15.0f, 15.0f);
		rotation_ = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(90.0f), D3DXToRadian(180.0f));
		D3DXMatrixIdentity(&Matrix_.world);
		D3DXMatrixIdentity(&Matrix_.position);
		D3DXMatrixIdentity(&Matrix_.rotation);
		D3DXMatrixIdentity(&Matrix_.scale);
	}
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	static void SetTargetBone(D3DXMATRIX TargetBone);
	static Shiled* Create(int _Priority);
private:
	Entity::MATRIX3D Matrix_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 scale_;
	D3DXVECTOR3 rotation_;
	static D3DXMATRIX TargetBone_;
};

