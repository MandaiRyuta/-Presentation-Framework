#pragma once

#include "../../../../Entity/Entity.h"
#include "../../../GameObjectManager/GameObjectManager.h"

class Sword : public GameObjectManager
{
public:
	Sword(int _priority) : GameObjectManager(_priority)
	{
		position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scale_ = D3DXVECTOR3(15.0f, 15.0f, 15.0f);
		rotation_ = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(45.0f), D3DXToRadian(-45.0f));
	}
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;
	static void SetTargetBone(D3DXMATRIX TargetBone);
	static Sword* Create(int _priority);
	static D3DXMATRIX GetMtxWorld();
private:
	Entity::MATRIX3D Matrix_;
	Entity::Dx9Buffer buffer_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 scale_;
	D3DXVECTOR3 rotation_;
	LPD3DXEFFECT effect_;

	static D3DXMATRIX TargetBone_;
	static D3DXMATRIX mtxworld_;
};

