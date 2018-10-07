#include "Light.h"

void Light::Init()
{
	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(mat));
	CreateMaterialLight(mat);

	ZeroMemory(&lightinfo_, sizeof(lightinfo_));
	lightinfo_.color = { 0.3f, 0.3f, 0.3f, 0.3f };
	CreateLight(lightinfo_);
}

void Light::CreateMaterialLight(D3DMATERIAL9 mat)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	mat.Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	mat.Ambient = { 0.7f,0.7f,0.7f,0.7f };

	device->SetMaterial(&mat);
}

void Light::CreateLight(Entity::LightInfo _light)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	_light.light.Type = D3DLIGHT_DIRECTIONAL;

	D3DXVECTOR3 vecDirection(-250.0f, 300.0f, 250.0f);

	D3DXVec3Normalize((D3DXVECTOR3*)&_light.light.Direction, &vecDirection);

	_light.light.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	_light.light.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	_light.light.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	device->SetLight(0, &_light.light);
	device->LightEnable(0, true);
	device->SetRenderState(D3DRS_AMBIENT, _light.color);
}
