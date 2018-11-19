#include "PlayerWeapon.h"
#include "../../../../LoadManager/ModelLoder.h"
#include "../../../../ShaderManager/EffectShaderManager.h"

void Sword::Init(LPDIRECT3DDEVICE9 _device)
{
	ModelLoder::GetModelData(SWORDMODEL)->color = D3DCOLOR_RGBA(255, 255, 255, 255);
}

void Sword::Update()
{
	D3DXMatrixScaling(&Matrix_.scale, scale_.x, scale_.y, scale_.z);
	D3DXMatrixTranslation(&Matrix_.position, position_.x, position_.y, position_.z);
	D3DXMatrixRotationYawPitchRoll(&Matrix_.rotation, rotation_.x, rotation_.y, rotation_.z);
}

void Sword::Draw(LPDIRECT3DDEVICE9 _device, D3DXMATRIX TargetBone)
{
	Matrix_.world = Matrix_.scale * Matrix_.rotation * Matrix_.position * TargetBone;
	// フィルタ設定
	_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//ライトを無効にする
	_device->LightEnable(0, true);
	// ライトの計算処理をしない
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);

	//マテリアルの設定
	_device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	_device->SetTransform(D3DTS_WORLD, &Matrix_.world);

	EffectShaderManager::GetEffect(SWORD)->SetTechnique("tecMinimum");
	EffectShaderManager::GetEffect(SWORD)->SetMatrix("mWVP", (D3DXMATRIX*)&Matrix_.world);
	EffectShaderManager::GetEffect(SWORD)->Begin(NULL, 0);

	for (DWORD i = 0; i < ModelLoder::GetModelData(SWORDMODEL)->dw_material; i++)
	{
		_device->SetTexture(0, ModelLoder::GetModelData(SWORDMODEL)->p_meshtexture[i]);
		ModelLoder::GetModelData(SWORDMODEL)->p_mesh->DrawSubset(i);
	}

	EffectShaderManager::GetEffect(SWORD)->End();
}

void Sword::Uninit()
{
	if (EffectShaderManager::GetEffect(SWORD) != nullptr)
	{
		EffectShaderManager::GetEffect(SWORD)->Release();
	}
	delete[] ModelLoder::GetModelData(SWORDMODEL)->p_meshtexture;
	delete[] ModelLoder::GetModelData(SWORDMODEL)->p_meshmaterial;
}
