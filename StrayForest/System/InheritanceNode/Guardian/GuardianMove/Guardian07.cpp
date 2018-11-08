#include "Guardian07.h"
#include "../../Player/Player.h"
void Guardian07::Update(Entity::MATRIX3D& _matrix)
{
	D3DXMATRIX RotVec;
	D3DXMatrixTranslation(&RotVec, Player::GetPlayerMatrix()._41 + 10.0f, Player::GetPlayerMatrix()._42 + 15.0f, Player::GetPlayerMatrix()._43 + 10.0f);

	D3DXMatrixTranslation(&_matrix.position, Player::GetPlayerMatrix()._41, Player::GetPlayerMatrix()._42 + 15.0f, Player::GetPlayerMatrix()._43);
	float x = RotVec._41 - _matrix.position._41;
	float y = RotVec._42 - _matrix.position._42;
	float z = RotVec._43 - _matrix.position._43;
	float fx = x * cosf(time_) - z * sinf(time_) + _matrix.position._41;
	float fy = x * cosf(time_) - y * sinf(time_) + _matrix.position._42;
	float fz = x * sinf(time_) + z * cosf(time_) + _matrix.position._43;
	D3DXMatrixTranslation(&_matrix.position, fx, fy, fz);
	D3DXMatrixScaling(&_matrix.scale, 2.0f, 2.0f, 2.0f);
	D3DXMatrixRotationYawPitchRoll(&_matrix.rotation, fx, fy, fz);

	_matrix.world = _matrix.scale * _matrix.rotation * _matrix.position;
	time_ -= 0.1f;
}
