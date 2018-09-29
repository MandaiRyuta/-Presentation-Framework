#pragma once
#include "../Entity.h"

class TargetRotation : public Entity
{
public:
	TargetRotation(D3DXVECTOR3 _rotation)
		: rotation_(_rotation)
	{
		D3DXMatrixIdentity(&mtx_rotation_);
	}

	void ConfigurationVector3(D3DXVECTOR3 _rotation) { rotation_ = _rotation; }
	void ConfigurationMatrix() { D3DXMatrixScaling(&mtx_rotation_, rotation_.x, rotation_.y, rotation_.z); }
public:
	D3DXVECTOR3 GetVector3() const { return rotation_; }
	D3DXMATRIX GetMatrix() const { return mtx_rotation_; }

	void SetVector3(D3DXVECTOR3 _rotation) { rotation_ = _rotation; }
	void SetMatrix(D3DXMATRIX _mtx_rotation) { mtx_rotation_ = _mtx_rotation; }
private:
	D3DXVECTOR3 rotation_;
	D3DXMATRIX mtx_rotation_;
};
