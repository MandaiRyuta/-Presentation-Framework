#pragma once

#include "../../../../Entity/Entity.h"
#include <vector>

class PlayerShiled
{
public:
	virtual ~PlayerShiled() {}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX TargetBone) = 0;
	virtual void Uninit() = 0;
};

class Shiled : public PlayerShiled
{
public:
	Shiled()
	{
		position_ = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
		scale_ = D3DXVECTOR3(15.0f, 15.0f, 15.0f);
		rotation_ = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(90.0f), D3DXToRadian(180.0f));
	}
	void Init() override;
	void Update() override;
	void Draw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX TargetBone) override;
	void Uninit() override;
private:
	Entity::MATRIX3D Matrix_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 scale_;
	D3DXVECTOR3 rotation_;
};

