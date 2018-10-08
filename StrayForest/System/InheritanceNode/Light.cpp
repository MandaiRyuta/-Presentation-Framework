#include "Light.h"

D3DXVECTOR3 Light::lightpos_;

void Light::Init()
{
	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(mat));
	CreateMaterialLight(mat);

	ZeroMemory(&lightinfo_, sizeof(lightinfo_));
	lightinfo_.color = { 0.3f, 0.3f, 0.3f, 0.3f };
	CreateLight(lightinfo_);
}

void Light::CreateMaterialLight(D3DMATERIAL9 _mat)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	_mat.Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	_mat.Ambient = { 0.7f,0.7f,0.7f,0.7f };

	device->SetMaterial(&_mat);
}

void Light::CreateLight(Entity::LightInfo _light)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	_light.light.Type = D3DLIGHT_DIRECTIONAL;

	lightpos_ = D3DXVECTOR3(-250.0f, 300.0f, 250.0f);

	D3DXVec3Normalize((D3DXVECTOR3*)&_light.light.Direction, &lightpos_);

	_light.light.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	_light.light.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	_light.light.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	device->SetLight(0, &_light.light);
	device->LightEnable(0, true);
	device->SetRenderState(D3DRS_AMBIENT, _light.color);
}

D3DXVECTOR3 Light::GetLightPos()
{
	return lightpos_;
}

void Light::SetLightPos(D3DXVECTOR3 _pos)
{
	lightpos_ = _pos;
}
