#include "PlayerWeapon.h"
#include "../../../../LoadManager/ModelLoder.h"
#include "../../../../ShaderManager/EffectShaderManager.h"
#include "../../../Renderer/GameManager.h"

D3DXMATRIX Sword::mtxworld_;
D3DXMATRIX Sword::TargetBone_;

void Sword::Init()
{
}

void Sword::Update()
{
	D3DXMatrixScaling(&Matrix_.scale, scale_.x, scale_.y, scale_.z);
	D3DXMatrixTranslation(&Matrix_.position, position_.x, position_.y, position_.z);
	D3DXMatrixRotationYawPitchRoll(&Matrix_.rotation, rotation_.x, rotation_.y, rotation_.z);
}

void Sword::Draw()
{
	LPDIRECT3DDEVICE9 _device = GetDevice();
	Matrix_.world = Matrix_.scale * Matrix_.rotation * Matrix_.position * TargetBone_;

	mtxworld_ = Matrix_.world;
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

	for (DWORD i = 0; i < GameManager::GetModel(LOADMODEL::MODEL_SWORD)->GetModelData()->dw_material; i++)
	{
		_device->SetTexture(0, GameManager::GetModel(LOADMODEL::MODEL_SWORD)->GetModelData()->p_meshtexture[i]);
		GameManager::GetModel(LOADMODEL::MODEL_SWORD)->GetModelData()->p_mesh->DrawSubset(i);
	}

	EffectShaderManager::GetEffect(SWORD)->End();
}

void Sword::Uninit()
{
}

void Sword::SetTargetBone(D3DXMATRIX TargetBone)
{
	TargetBone_ = TargetBone;
}

Sword * Sword::Create(int _priority)
{
	Sword* sword = new Sword(_priority);
	sword->Init();
	return sword;
}

D3DXMATRIX Sword::GetMtxWorld()
{
	return mtxworld_;
}
