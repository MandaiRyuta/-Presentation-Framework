#include "Skydome.h"
#include "../../ShaderManager/EffectShaderManager.h"
#include "../../LoadManager/ModelLoder.h"
#include "Camera.h"
void Skydome::Init()
{
	//LPDIRECT3DDEVICE9 device = GetDevice();

	D3DXMatrixIdentity(&matrix_.position);
	D3DXMatrixIdentity(&matrix_.scale);
	D3DXMatrixIdentity(&matrix_.rotation);

	D3DXMatrixTranslation(&matrix_.position, 0.0f, 100.0f, 0.0f);
	D3DXMatrixScaling(&matrix_.scale, 8.0f, 8.0f, 8.0f);
}

void Skydome::Update()
{
	static float domerotation = 0.0f;
	D3DXMatrixRotationYawPitchRoll(&matrix_.rotation, domerotation, 0.0f, 0.0f);
	
	matrix_.world = matrix_.scale * matrix_.rotation * matrix_.position;
}

void Skydome::Draw()
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mWVP = matrix_.world * CCamera::GetView() * CCamera::GetProj();
	// ƒŒƒ“ƒ_ƒŠƒ“ƒO
	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
	device->SetRenderState(D3DRS_ZENABLE, true);
	EffectShaderManager::GetEffect(MODEL3D)->SetTechnique("tecMinimum");
	EffectShaderManager::GetEffect(MODEL3D)->SetMatrix("mWVP", &mWVP);
	EffectShaderManager::GetEffect(MODEL3D)->Begin(NULL, 0);
	EffectShaderManager::GetEffect(MODEL3D)->BeginPass(0);
	
	for (DWORD i = 0; i < ModelLoder::GetModelData(SKYDOME)->dw_material; i++)
	{
		EffectShaderManager::GetEffect(MODEL3D)->SetTexture("texDecal", ModelLoder::GetModelData(SKYDOME)->p_meshtexture[i]);
		ModelLoder::GetModelData(SKYDOME)->p_mesh->DrawSubset(i);
	}

	EffectShaderManager::GetEffect(MODEL3D)->EndPass();
	EffectShaderManager::GetEffect(MODEL3D)->End();
}

void Skydome::Uninit()
{
	if (ModelLoder::GetModelData(SKYDOME)->p_mesh != nullptr)
	{
		ModelLoder::GetModelData(SKYDOME)->p_mesh->Release();
		ModelLoder::GetModelData(SKYDOME)->p_mesh = nullptr;
	}
	if (ModelLoder::GetModelData(SKYDOME)->p_meshtexture != nullptr)
	{
		delete[] ModelLoder::GetModelData(SKYDOME)->p_meshtexture;
	}
	if (ModelLoder::GetModelData(SKYDOME)->p_meshmaterial != nullptr)
	{
		delete[] ModelLoder::GetModelData(SKYDOME)->p_meshmaterial;
	}
}

Skydome * Skydome::Create()
{
	Skydome* CreateSkydome = new Skydome();
	CreateSkydome->Init();

	return CreateSkydome;
}
