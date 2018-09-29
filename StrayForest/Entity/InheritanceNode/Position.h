#pragma once
#include "../Entity.h"

class TargetPosition : public Entity
{
public:
	TargetPosition() 
		: position_()
	{
		D3DXMatrixIdentity(&mtx_position_);
	}
	void ConfigurationVector3(D3DXVECTOR3 _position) { position_ = _position; }
	void ConfigurationMatrix() { D3DXMatrixScaling(&mtx_position_, position_.x, position_.y, position_.z); }
public:
	D3DXVECTOR3 GetPosition() const { return position_; }
	D3DXMATRIX GetMtxPosition() const { return mtx_position_; }

	void SetPosition(D3DXVECTOR3 _position) { position_ = _position; }
	void SetMtxPosition(D3DXMATRIX _mtx_position) { _mtx_position = mtx_position_; }
private:
	D3DXVECTOR3 position_;
	D3DXMATRIX mtx_position_;
};
