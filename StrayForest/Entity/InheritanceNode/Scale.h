#pragma once
#include "../Entity.h"
class TargetScale : public Entity
{
public:
	TargetScale(D3DXVECTOR3 _scale) 
		: scale_(_scale)
	{
		D3DXMatrixIdentity(&mtx_scale_);
	}

	void ConfigurationVector3(D3DXVECTOR3 _scale) { scale_ = _scale; }
	void ConfigurationMatrix() { D3DXMatrixScaling(&mtx_scale_, scale_.x, scale_.y, scale_.z); }
public:
	D3DXVECTOR3 GetVector3() const { return scale_; }
	D3DXMATRIX GetMatrix() const { return mtx_scale_; }

	void SetVector3(D3DXVECTOR3 _scale) { scale_ = _scale; }
	void SetMatrix(D3DXMATRIX _mtx_scale) { mtx_scale_ = _mtx_scale; }
private:
	D3DXVECTOR3 scale_;
	D3DXMATRIX mtx_scale_;
};