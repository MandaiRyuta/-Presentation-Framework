#include "PlayerShiled.h"
#include "../../../../LoadManager/ModelLoder.h"
#include "../../../../ShaderManager/EffectShaderManager.h"
#include "../../../Renderer/GameManager.h"

D3DXMATRIX Shiled::TargetBone_;

void Shiled::Init()
{
}

void Shiled::Update()
{
	D3DXMatrixScaling(&Matrix_.scale, scale_.x, scale_.y, scale_.z);
	D3DXMatrixTranslation(&Matrix_.position, position_.x, position_.y, position_.z);
	D3DXMatrixRotationYawPitchRoll(&Matrix_.rotation, rotation_.x, rotation_.y, rotation_.z);
}

void Shiled::Draw()
{
	LPDIRECT3DDEVICE9 _device = GetDevice();
	Matrix_.world = Matrix_.scale * Matrix_.rotation * Matrix_.position * TargetBone_;
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

	EffectShaderManager::GetEffect(SHILED)->SetTechnique("tecMinimum");
	EffectShaderManager::GetEffect(SHILED)->SetMatrix("mWVP", (D3DXMATRIX*)&Matrix_.world);
	EffectShaderManager::GetEffect(SHILED)->Begin(NULL, 0);

	for (DWORD i = 0; i < GameManager::GetModel(LOADMODEL::MODEL_SHILED)->GetModelData()->dw_material; i++)
	{
		_device->SetTexture(0, GameManager::GetModel(LOADMODEL::MODEL_SHILED)->GetModelData()->p_meshtexture[i]);
		GameManager::GetModel(LOADMODEL::MODEL_SHILED)->GetModelData()->p_mesh->DrawSubset(i);
	}
	EffectShaderManager::GetEffect(SHILED)->End();
}

void Shiled::Uninit()
{
	//delete[] ModelLoder::GetModelData(SHILEDMODEL)->p_meshtexture;
	//delete[] ModelLoder::GetModelData(SHILEDMODEL)->p_meshmaterial;
}

void Shiled::SetTargetBone(D3DXMATRIX TargetBone)
{
	TargetBone_ = TargetBone;
}

Shiled * Shiled::Create(int _Priority)
{
	Shiled* shiled = new Shiled(_Priority);
	shiled->Init();

	return shiled;
}
