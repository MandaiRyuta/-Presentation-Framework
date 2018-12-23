#pragma once

#include "../../../../Entity/Entity.h"
#include <vector>

class PlayerSword
{
public:
	virtual ~PlayerSword() {}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX TargetBone) = 0;
	virtual void Uninit() = 0;
};

class Sword : public PlayerSword
{
public:
	Sword()
	{
		position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scale_ = D3DXVECTOR3(15.0f, 15.0f, 15.0f);
		rotation_ = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(45.0f), D3DXToRadian(-45.0f));
	}
	void Init() override;
	void Update() override;
	void Draw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX TargetBone) override;
	void Uninit() override;
	static D3DXMATRIX GetMtxWorld();
private:
	Entity::MATRIX3D Matrix_;
	Entity::Dx9Buffer buffer_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 scale_;
	D3DXVECTOR3 rotation_;
	LPD3DXEFFECT effect_;

	static D3DXMATRIX mtxworld_;
};

